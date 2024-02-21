# KFS-2
in progress


## Global Descriptor Table (GDT):

The GDT is a system-wide table that contains descriptors for various memory segments. Each descriptor defines a segment of memory and includes information such as base address, limit, access rights, and segment type.
The GDT is typically set up by the operating system during system initialization and is stored in memory. It provides a way for the operating system to control and manage memory access for different tasks or processes.
The GDT is divided into entries, and each entry is a descriptor that defines a specific segment of memory. These segments could include code segments, data segments, and stack segments.
The GDT is loaded into the processor's memory management unit (MMU), which uses it to translate virtual addresses to physical addresses and enforce memory protection.
#### Analogie 
Imagine a library with a central catalog that contains information about all the books available in the library. This catalog is like the GDT. It's a system-wide reference that provides details about different categories of books, such as fiction, non-fiction, and reference materials.
Each entry in the catalog (GDT) describes a specific section or category of books, including its location, access rules (who can access it), and any special conditions (such as borrowing restrictions). The catalog is managed centrally and used by everyone in the library to find and access books.

**selector : A segment selector is a numeric value stored in a segment register. It is used in conjunction with an offset to form a logical address. The combination of a segment selector and an offset produces a unique**


## Definitions of properties:

#### Each entry of GDT have this follow property:<br/>

| Property name   | definition  |
| ------------ | ------------ |
| **Base Address**  |The base address of the segment. Specifies the starting   |
|   **Limit**| The limit of the segment, indicating the size of the segment.  |
| **Type**  |  Indicates whether the segment is a code segment or a data segment. |
| **Privilege Level**  | Specifies the privilege level of the segment. Ring 0 is the most privileged (kernel mode), and Ring 3 is the least privileged (user mode  |
| **Present**  | Indicates whether the segment is present in memory (1 for present, 0 for not present).  |
| **Read/Write**  |For data segments, specifies whether the segment is readable (1 for readable, 0 for not readable). For code segments, specifies whether the segment is writable (1 for writable, 0 for not   |
| **Executable:**  | For code segments, specifies whether the segment is executable (1 for executable, 0 for not executable). For data segments, specifies whether the segment is conforming (1 for conforming, 0 for not conforming).  |
|**Granularity**|Segmentation Granularity In memory segmentation, the granularity refers to the size of individual memory segments. Each segment has a base address and a limit, and the granularity determines the size of each segment. For example, if the granularity is 4 KB, each segment is 4 KB in size, and the system can allocate memory in 4 KB chunks|

[GDT implementation property](https://www.youtube.com/watch?v=Wh5nPn2U_1w)

# Segment

In the context of computer architecture, a memory segment refers to a contiguous block of memory with a specific purpose or attributes. Memory segmentation is a memory management technique used in certain architectures, such as x86 and x86-64. Segmentation divides the memory into logical segments, each with its own base address and size.
The x86 line of computers have 6 segment registers (CS, DS, ES, FS, GS, SS). They are totally independent of one another.

| Register         | Purpose                                                                       | Usage                                                                                                                                                               |
|------------------|-------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **CS (Code Segment)**   | Contains the selector for the code segment, defining base address and size. | Instructions fetched for execution are retrieved from the memory location specified by the Code Segment selector.                                                |
| **DS (Data Segment)**   | Contains the selector for the data segment, used for general data storage.  | Data operands for instructions (e.g., memory access) are retrieved from the memory location specified by the Data Segment selector.                                 |
| **ES (Extra Segment)**   | Historically an extra data segment for additional data storage.              | Used with string manipulation instructions for extra data storage. In modern systems, often set to the same value as the Data Segment.                               |
| **FS and GS (Additional Segments)** | Additional data segments beyond Code and Data segments.             | Provide extra segment selectors for data storage, used in more complex memory models. In some OS, may have specific purposes like thread-local storage.          |
| **SS (Stack Segment)**   | Contains the selector for the stack segment, used for the program stack.    | Stack Segment selector specifies base address and size of the stack segment. Used for storing local variables, function parameters, and return addresses.           |

In modern operating systems and applications, especially those using a flat memory model, it's common to set most of these segment registers to the same value to simplify memory access. In protected mode and long mode (on x86-64), segmentation is often used for privilege separation and memory protection.


To clarify:
Each of these segment registers is 16 bits wide means that the values these registers can hold are 16 bits in size.
The registers themselves may have a physical size that is larger than 16 bits, but they are designed to hold 16-bit values.
So, while the registers are physically located in the processor, they operate based on 16-bit values for memory segmentation purposes. The actual data they hold, the segment selectors, are used to reference specific segments in memory.

# A logical address, also known as a virtual address

- A logical address, also known as a virtual address :
is an address generated by a program or a process in the context of virtual memory. In modern computer systems, the memory addressing model is often divided into two spaces: logical (virtual) address space and physical address space.

- Logical (Virtual) Address Space:
The logical address space is the range of addresses that a program or process can use. Each process has its own separate logical address space, and it doesn't directly correspond to the physical layout of memory.
Logical addresses are generated by the CPU during program execution and are used by the program to reference memory locations.
- Import and save files from GitHub, Dropbox, Google Drive and One Drive
- Virtual Memory:
is a memory management technique that provides an "illusion" to processes that each one has its own dedicated space in the entire addressable memory range.
Logical addresses in virtual memory are mapped to physical addresses, which represent the actual locations in physical RAM.
- Address Translation:
The operating system, along with the memory management unit (MMU) of the CPU, is responsible for translating logical addresses to physical addresses. This translation is done using data structures such as page tables.
The mapping allows the operating system to move data in and out of physical memory (RAM) as needed, providing the illusion of a larger memory space than is physically available
- Logical Address Calculation:
A logical address in the x86 architecture is typically expressed as a combination of a segment selector and an offset within that segment. The actual memory address is calculated using the formula: Physical Address = Base Address of Segment + Offset.


# Real mode

Real mode is a processor operating mode in x86 architecture, and it is one of the initial modes that the CPU can operate in during the early stages of system boot-up. Real mode is a compatibility mode designed to provide backward compatibility with the Intel 8086 and 8088 processors, the predecessors of modern x86 CPUs.

Here are key characteristics of real mode:

Memory Addressing:

Real mode uses a 20-bit address bus, allowing it to address up to 1 MB of memory. Memory addresses are specified as segments and offsets, and the physical address is calculated as segment * 16 + offset.
Segmentation:

Memory is divided into segments, each 64 KB in size. Segment registers (CS, DS, ES, SS) hold the segment value, and the offset is added to it to generate the physical address.
No Memory Protection:

Real mode lacks memory protection mechanisms. Any program can access any part of the memory, which can lead to accidental overwrites and crashes.
Interrupts:

Interrupt handling in real mode involves using an Interrupt Vector Table (IVT), and interrupts are identified by a single-byte interrupt number.
Registers:

Real mode provides a set of general-purpose registers, such as AX, BX, CX, and DX, with 16-bit sizes. It lacks many of the advanced features found in later operating modes.
Real mode is commonly used during the boot process of a computer system. Boot loaders and early-stage operating system components are often executed in real mode before transitioning to protected mode or other advanced modes that provide more sophisticated memory protection and multitasking capabilities.

It's important to note that while real mode is still present in modern x86 processors for compatibility reasons, contemporary operating systems generally switch to protected mode or long mode (for 64-bit systems) to take advantage of advanced features and better memory protection mechanisms.

# Protected mode

Protected mode is a mode of operation for x86 processors that provides hardware-level memory protection, multitasking, and privilege levels. It's a feature of the x86 architecture that was introduced with the 80286 processor and continued with later processors. In protected mode, the CPU provides a set of features that enhance the robustness and security of the system.

**Analogy with Real World:**
Imagine a bustling city with various buildings, each serving a different purpose—residential buildings, offices, banks, and government facilities. Now, let's draw an analogy:

1. **Real Mode (DOS Era):**
   - Real mode is like a small village where everyone lives in simple houses, and there's no clear distinction between private and public spaces.
   - It's easy for anyone to access or modify any part of the village, leading to potential chaos if someone behaves recklessly.

2. **Protected Mode (Modern City):**
   - Protected mode is akin to a modern city with skyscrapers, residential areas, commercial districts, and government buildings.
   - Each building represents a different part of the system (e.g., user space, kernel space, device drivers).
   - Memory protection is like security measures in place. Residential areas (user space) are separate from corporate offices (kernel space), and access is controlled.
   - Multitasking is like people working in various offices simultaneously, each unaware of what others are doing.

In protected mode:
- **Memory Protection:** Each "building" (segment) has its own set of rules, and one cannot easily interfere with the affairs of another.
- **Privilege Levels:** There are different privilege levels, like different security clearances. Some operations are allowed only at higher privilege levels (closer to the kernel).
- **Multitasking:** Multiple tasks (processes) can run concurrently without interfering with each other.

This analogy simplifies the concept, but it captures the essence of how protected mode brings order, security, and multitasking capabilities to the x86 architecture. Modern operating systems, such as Windows and Linux, leverage protected mode for enhanced stability and security.



## Local descriptor table:

The Local Descriptor Table (LDT) is a data structure similar to the Global Descriptor Table (GDT) in x86 architecture. Both the GDT and LDT are used for managing memory segmentation and access control. However, there are key differences:

1. **Scope:**
   - **GDT (Global Descriptor Table):** The GDT is a system-wide table that is shared among all processes and threads. It is used to define global segment descriptors.
   - **LDT (Local Descriptor Table):** The LDT is specific to each process or thread. Each process/thread can have its own LDT, and the LDT is used to define local segment descriptors for that particular process/thread.

2. **Purpose:**
   - **GDT:** It is primarily used for defining global memory segments such as code, data, and stack segments. The GDT is shared among all processes and is typically set up by the operating system during system initialization.
   - **LDT:** It allows individual processes to have their own set of segment descriptors with different access permissions. This provides a level of isolation between processes.

3. **Usage:**
   - **GDT:** Commonly used for system-level segments and shared memory areas.
   - **LDT:** Used for process-specific segments, enabling processes to have their own custom memory protection settings.

The use of LDT has become less common in modern operating systems. Most modern operating systems rely on the GDT and other mechanisms for memory protection and process isolation. The x86 architecture provides a way to load and switch between different LDTs using the `lldt` instruction.

It's important to note that the LDT is an optional feature, and its usage has diminished over time. In modern systems, the GDT, along with other features like paging, provides sufficient memory protection and isolation for processes.


The Global Descriptor Table (GDT) is a data structure used by the x86 architecture to define memory segments and their access attributes. It plays a crucial role in memory protection and privilege level management in the x86 architecture.

Here's a high-level overview of how the GDT works with the processor and memory:

1. **Segmentation and Memory Protection:**
   - The x86 architecture supports segmentation, where the memory is divided into segments, and each segment is assigned specific attributes.
   - The GDT contains entries for various segments, such as code, data, and stack segments. Each entry specifies the base address, limit, access rights, and other attributes for a segment.

2. **Descriptor Loading:**
   - During system initialization, the operating system sets up the GDT with the necessary segment descriptors.
   - The GDT is loaded into memory, and its location and size are stored in the Global Descriptor Table Register (`GDTR`).

3. **Privilege Levels:**
   - Each segment descriptor in the GDT has an associated privilege level (0 to 3). This indicates the privilege level required to access the segment.
   - The processor operates at a particular privilege level, and access to segments is restricted based on privilege levels. For example, user code typically runs at privilege level 3 (user mode), while kernel code runs at privilege level 0 (kernel mode).

4. **Memory Access Checks:**
   - When a memory access is attempted, the processor checks the GDT to determine the access rights and privilege level required for the specified segment.
   - If the access violates the access rights or privilege level, a processor exception (e.g., a general protection fault) is triggered.

5. **Task Switching and TSS:**
   - The GDT may also include entries for Task State Segments (TSS) used in task switching.
   - Task switching involves switching between different execution contexts, such as switching between user and kernel modes or switching between different tasks.

6. **Loading GDTR:**
   - The `lgdt` instruction is used to load the GDTR, informing the processor about the location and size of the GDT.

7. **Enabling Protection:**
   - The most significant bit of the Control Register 0 (CR0) is the Protection Enable (PE) bit. Setting this bit enables memory protection, and it is typically set after loading the GDT.

8. **Segment Register Loading:**
   - Once the GDT is loaded and protection is enabled, the operating system sets up segment registers (e.g., `cs`, `ds`, `es`, `ss`) with appropriate segment selectors pointing to entries in the GDT.

Overall, the GDT serves as a mechanism for the x86 architecture to manage memory segmentation, protection, and privilege levels, providing a foundation for secure and controlled execution of code in different parts of the system.
