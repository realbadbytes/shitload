from a raw stream of bytes:
load as ELF with proper relocations
call main, run code, then return control to original process

stages:

(1) normal process
(2) throw exploit
(3) run stage 1 shellcode, which is *this* loader
(4) wait for byte stream
(5) interpret byte stream as ELF
(6) run ELF, return control to process


