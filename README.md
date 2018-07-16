# Astra Keyfob

A set of scripts to determine and construct the code used in 1999 - 2004 Astra keyfobs.

Data is transferred at 9600 baud using IEEE 802.3 (high -> low = '0') manchester encoding.

timing.jpg shows the order in which bits are sent. 

Given a .csv in format 'time (s) | data' generateCode.m will determine the 97 bit unique code and the 34 bit incrementing code.

It produces two arrays which can be coppied into 'Astra_Keyfob.ino' to send the duplicated code over a 433MHz RF connection.

Before writing 'Astra_Keyfob.ino' I believed that an enumeration risk existed and was attempting to exploit this to predict the future codes. However I failed to notice that the 97 bit unique code changed every press and appears to be random, wheras I previously thought that it was a static code which was unique to the open/close of each key fob. 

As such these tools are no real use however as they were already written I thought I might as well upload them.
