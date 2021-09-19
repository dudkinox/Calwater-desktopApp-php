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
   "ÄC Åue Çe Éa Ñae Öa Üa ác àe âe äe ãi åi çi éAE èA ",
   "êE ëee íAE ìo îoe ïo ñu óu òy ôOE öUE õc ústlg ùyen ",
   "ûpeseta üflorin †a °i ¢o £u §n •N ¶a ßo ®? ©+ ™+ ",
   "´.5 ¨.25 ≠! Æ<< Ø>> ≥| ¥| µ| ∂| ∑+ ∏+ π| ∫| ª+ º+ ",
   "Ω+ æ+ ø+ ¿+ ¡- ¬- √| ƒ- ≈+ ∆| «| »+ …+  - À- Ã| Õ- ",
   "Œ+ œ- –- —- “- ”+ ‘+ ’+ ÷+ ◊+ ÿ+ Ÿ+ ⁄+ ‡a ·ss „pi ",
   "‰Sigma ÂRho ÁTau ÈTheta ÍOmega Îdelta Ìo ÓEpsilon ",
   "= Ò+/- Ú>= Û<= ˆ/ ˘o ˙. ˚sqrt ¸^n ˝^2"
   };

