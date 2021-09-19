##
##  Sample character translation resource file for
##  WinPMail v1.02, SMTP translation.
##  Copyright (c) 1993, David Harris, All Rights Reserved.
##
##  This file can be used to replace the default SMTP
##  translation table used by PMail on outgoing non-MIME
##  messages.
##
##  Resource 0 in the file must be an SMTP translation table:
##  it consists of high-bit characters followed immediately
##  by the string of characters which PMail should use in
##  place of the character in outgoing messages. Spaces
##  delimit each entry.
##
##  To use this file, make any necessary changes to it and
##  compile it using the command "ResCom WPM-CHAR.R". Copy
##  the resulting WPM-CHAR.RSC file into either your home
##  mailbox if you want it to affect only you, or into the
##  same directory as WINPMAIL.EXE if you want it to affect
##  all users on the system.
##

text TEXT_SMTP_TABLE
   {
   "�C �ue �e �a �ae �a �a �c �e �e �e �i �i �i �AE �A ",
   "�E �ee �AE �o �oe �o �u �u �y �OE �UE �c �stlg �yen ",
   "�peseta �florin �a �i �o �u �n �N �a �o �? �+ �+ ",
   "�.5 �.25 �! �<< �>> �| �| �| �| �+ �+ �| �| �+ �+ ",
   "�+ �+ �+ �+ �- �- �| �- �+ �| �| �+ �+ �- �- �| �- ",
   "�+ �- �- �- �- �+ �+ �+ �+ �+ �+ �+ �+ �a �ss �pi ",
   "�Sigma �Rho �Tau �Theta �Omega �delta �o �Epsilon ",
   "�= �+/- �>= �<= �/ �o �. �sqrt �^n �^2"
   };

