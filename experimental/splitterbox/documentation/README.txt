Prototype Simulator Splitter Box

Allows up to 6 PCs to be connected to one Simulator Interface.
 - PCs are USB connected, USB-A powers the splitter box PCB, so is always connected.
 - PCs on USB-B to USB-F do not power the splitter.
 - Interface is RS232 connected, NOT powered off the splitter box PCB (so uses a std cable and PSU).
 - Uses standard FTDI USB Virtual COM Port drivers.

3 Modes of operation:

Pass-Through : 
 - 2-way IO between the Simulator Interface RS232 port and the PC on USB-A
 - LED is Red.
 - Conventional simulator operation, allows the Interface to be configured from the PC (e.g.
   Abel delays, CLI commands).

Shared : 
 - Data incoming from the Simulator Interface RS232 port is distributed and remapped
   to all USB ports.
 - So physical bell 1 can be signal 1 on USB-A, physical bell 2 can be a signal
   on USB-B (including being remapped to signal 1), etc, etc.
 - LED is Green.
 - In the current code in this mode the USB ports are never read, but the lines are wired
   up on the PCB.
 - Supports remapping to bells IDs 13-16 (ABCD) and switch signals (WXYZ). 

Config : 
 - 2-way IO between the Splitter Box firmware and the PC on USB-A.
 - LED is flashing green/red.
 - CLI commands for configuring the Splitter Box firmware, signal mappings and so on. 

Refer to the source code for more details.

Prototype is functional, but requires more work to get to a usable product.
Could perhaps be expanded to support more USB ports by creating a custom "transmit-only"
version of SoftwareSerial for ports other than USB-A.

PCB: https://oshpark.com/shared_projects/ameUqaLq
