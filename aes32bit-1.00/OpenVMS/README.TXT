To build and run aes32bit.exe on OpenVMS the
following steps are necessary:

1) Set the default device and directory to
   aes32bit's src directory:
   set def some$dev[home.of.aes32bit.src]

2) Execute MMS:
   mms/description=[-.OpenVMS]descrip.mms

3) Define a command verb:
   aes32bit :== $some$dev[home.of.aes32bit.src]aes32bit.exe

4) Run aes32bit and read usage information:
   aes32bit
