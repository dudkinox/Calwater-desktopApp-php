BEARHTML  

BEARHTML is middleware sitting between Pegasus Mail and an Html file viewer.  
It is intended as an alternative to HTS in Pegasus Mail for rendering Html message content. 
It is not an editor for preparing Html messages, and neither is it an Html browser .

That being said the (first) installation is simple (from either the main Pegasus Mail site,
or my direct update site: http://www3.telus.net/public/irelam/

1. Shutdown Pegasus Mail
2. Download Bearnnn.zip (containing bearhtml.dll), BearSupport.zip and Bearxx.zip 
   (where xx is country code for translated helpfiles). Eg Bearen.zip for English helpfiles.
   Extract content of zips into the Pegasus Mail executables directory.
3. Create an empty file using notepad, called bearhtml.log in the Pegasus Mail NewMail directory,
   ie C:\pmail\mail\bearhtml.log (needed for tracing problems).
4.  Review/Edit Bearhtml.ini, BearWarn.txt, and BearLang.xx if required (xx= language code). 
5. Start Pegasus Mail.

What do I see?   Well nothing new (hopefully). For html messages in the New Mail and 
in normal message folders you should get the message rendered more accurately.

Distribution set
  
   The following files make up Bearhtml:

   Bearhtml.dll
   Bearhtml.ini
   Bearwarn.txt
   BearTidy.cfg
   Beartlds.txt
   LibTidy.dll
   BearGrfn.png
 
   Bearhlp-en.htm       (EN is country code)
   BearLang.en          (EN is country code)
   Bearhtml-readme.txt  (this file)
   BearDef.css
 
   Bearhtml.log (in your newmail directory)



Upgrades 

From time to time, announced in Forums (community.pmail.com) Newsgroups and my website, 
( http://www3.telus.net/public/irelam/ ) new versions of Bearhtml.dll and 
the helpfiles (Bearnnn.zip and Bearxx.zip) are made available.  
You can download these files (per steps 1 & 2 above) and replace existing versions.
Your options file, bearhtml.ini will not be replaced.


Limitations (intended)

1. Scripting languages, either imbedded or remote, such as Javascript are flushed/ignored but the webpage is rendered. 
This affects code that differentiates between browser engines (IE/Firefox). Cookies processing is also ignored.
2. In some cases remote images cannot be fetched as the Urls are incomplete and there is no <base> header tag coded. 

Options

At present the user interface for setting options is contained in Bearhtml.ini:


Martin Ireland
