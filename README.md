# HelloWorld FreeRTOS

A boilerplate educational project for learning **FreeRTOS** on the **STM32F4 Platform** (specifically designed for the **STM32F4 Discovery** board). 

This project uses the legacy **STM32F4xx Standard Peripheral Driver (StdPeriph)** library rather than the modern HAL/LL libraries, making it a perfect match for classic STM32 and RTOS courses. The project is pre-configured for **Atollic TrueSTUDIO**, but it can also be easily imported and converted to work in **STM32CubeIDE**.

---

## Technical Overview

*   **Microcontroller:** STM32F4 series (ARM Cortex-M4 with FPU)
*   **Operating System:** FreeRTOS Kernel
*   **Libraries:** STM32F4xx Standard Peripheral Library (CMSIS & StdPeriph)
*   **Development Toolchain:** Atollic TrueSTUDIO (GCC Toolchain)
*   **Linker Script:** `stm32f4_flash.ld` (configured for Flash-based execution)

---

## Directory Structure

```text
HelloWorld_FreeRTOS/
├── .settings/              # IDE settings
├── FreeRTOSConfig/         # FreeRTOS configuration file
│   └── FreeRTOSConfig.h    # Configures scheduler options, task priorities, heap size, etc.
├── Libraries/              # Hardware abstraction and low-level drivers
│   ├── CMSIS/              # ARM Cortex Core Peripheral Access Layer
│   ├── Device/             # STM32F4xx system start files
│   └── STM32F4xx_StdPeriph_Driver/ # Legacy STM32 Standard Peripheral Library (StdPeriph)
├── MiddleWares/            # Operating system source files
│   └── Third_Party/        # Contains the FreeRTOS Kernel code
├── src/                    # Main source code
│   ├── main.c              # Application entry point
│   ├── startup_stm32f40xx.s# Assembly startup file (vector table, stack setup, reset handler)
│   ├── stm32f4xx_conf.h    # Configures which StdPeriph drivers are enabled
│   ├── stm32f4xx_it.c/.h   # Interrupt handlers (SysTick, SVCall, PendSV for FreeRTOS)
│   ├── system_stm32f4xx.c  # Clock configuration (sets up PLL and system frequencies)
│   └── tiny_printf.c       # Lightweight printf/sprintf implementation for microcontrollers
├── Utilities/              # Board Support Packages (BSP) for STM32F4-Discovery
├── stm32f4_flash.ld        # Linker script defining memory regions (Flash & SRAM)
├── .project / .cproject    # Eclipse/Atollic TrueSTUDIO project files
├── .gitignore              # Configured to ignore compiled binaries and local IDE files
└── LICENSE                 # Open-source MIT License
```

---

## Getting Started

### Option A: Using Atollic TrueSTUDIO (Legacy)
1. Open **Atollic TrueSTUDIO**.
2. Select your workspace directory.
3. Go to **File -> Import...**
4. Select **General -> Existing Projects into Workspace** and click **Next**.
5. Browse and select the `HelloWorld_FreeRTOS` root directory.
6. Make sure "Copy projects into workspace" is **unchecked** so it stays in place, then click **Finish**.
7. Click **Build** (the hammer icon) to compile the project.

### Option B: Importing to STM32CubeIDE (Modern)
Since Atollic TrueSTUDIO was acquired by STMicroelectronics and merged into **STM32CubeIDE**, you can easily convert this project:
1. Open **STM32CubeIDE**.
2. Go to **File -> Import...**
3. Select **General -> Import Atollic TrueSTUDIO Project** (or **Existing Projects into Workspace**).
4. Browse to the root of this project and follow the prompts. STM32CubeIDE will automatically detect and convert the Eclipse project structure to the STM32CubeIDE project format.
5. Build and debug natively in STM32CubeIDE.

---

## FreeRTOS Kernel Architecture & Core Files

To help you learn the internals of FreeRTOS, here is a detailed breakdown of what the core files located in `MiddleWares/Third_Party/FreeRTOS/org/Source/` do:

### 1. Core Kernel Modules
*   **`tasks.c`**: The absolute heart of the FreeRTOS kernel. It handles the lifetime of tasks (creation, deletion, and state transitions), the scheduling algorithms (priority-based preemptive scheduling), and context switching between tasks.
*   **`list.c`**: Implements a highly optimized circular doubly-linked list data structure (`List_t`). This is the internal backbone used by the kernel to keep track of tasks in various states (e.g., Ready Tasks list, Blocked/Delayed Tasks list, Suspended Tasks list). Almost all other FreeRTOS source files depend on `list.c`.
*   **`queue.c`**: Implements the message queue mechanism used for inter-task communication (passing data between tasks) and synchronization. Since binary semaphores, counting semaphores, and mutexes in FreeRTOS are actually built on top of queues, this file also handles their core synchronization logic.

### 2. Optional/Advanced Modules
*   **`timers.c`**: Implements software timers. It allows you to schedule functions (callback functions) to be executed at a specific future time or periodically, without needing to spawn a dedicated hardware timer or a heavy task for each timer.
*   **`event_groups.c`**: Implements event groups (or event flags). These allow a task to wait in the Blocked state until a specific combination of bits/flags (representing binary events) is set by another task or an Interrupt Service Routine (ISR).
*   **`stream_buffer.c`**: Implements stream buffers and message buffers. These are lightweight, high-performance alternatives to queues, specifically optimized for one-to-one transfer scenarios (e.g., passing a continuous stream of bytes from a UART interrupt to a processing task).
*   **`croutine.c`**: Implements co-routines, which are cooperative, lightweight tasks that share a single stack to save RAM. *Note: Co-routines are rarely used in modern systems due to their severe limitations and are kept mostly for legacy support.*

### 3. Portability & Hardware Interaction (`portable/`)
FreeRTOS is highly portable because hardware-specific implementations are separated from the core kernel:
*   **`portable/GCC/ARM_CM4F/` (Port Code)**:
    *   **`port.c` / `portmacro.h`**: These files bridge the generic FreeRTOS scheduler with the STM32F4 CPU core (ARM Cortex-M4 with FPU). They handle:
        *   Configuring and starting the **SysTick** timer to generate the periodic RTOS tick interrupt.
        *   Triggering context switches via the **PendSV** exception.
        *   Saving and restoring the CPU registers (including the Cortex-M4's floating-point registers) during a context switch.
        *   Managing critical sections by temporarily disabling/enabling interrupts below a certain priority.
*   **`portable/MemMang/heap_4.c` (Memory Management)**:
    *   This is the heap allocation scheme selected for this project. It implements `pvPortMalloc()` and `vPortFree()`.
    *   `heap_4.c` works by allocating memory from a statically-allocated array inside the internal SRAM.
    *   Unlike simpler allocators, `heap_4` **coalesces** (merges) adjacent free memory blocks to dramatically minimize memory fragmentation, making it highly robust for systems where tasks, queues, or semaphores are created and deleted dynamically at runtime.

---

## FreeRTOS Configuration

The RTOS behavior can be customized by editing `FreeRTOSConfig.h`.

Key configurations pre-defined:
*   **SysTick Interrupt:** Configured to drive the FreeRTOS scheduler tick.
*   **Memory Management:** Dynamic allocation is enabled, with memory configurations customized to the STM32F4's internal SRAM.

---

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.
