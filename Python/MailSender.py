#!/usr/bin/python3.4
# Send an email!

from smtplib import SMTP_SSL
from email.parser import HeaderParser

# If the e-mail headers are in a file, uncomment these two lines:
# with open(messagefile) as fp:
#     headers = Parser().parse(fp)

# This is an email.message.Message!
# Or for parsing headers in a string, use:
headers = HeaderParser().parsestr("From: 961950442@qq.com\n"
				"To: 2307849251@qq.com\n"
        		"Subject: Test message\n"
        		"\n"
        		"I love you, you know!\n"
        		"----python..\n")
# print(type(headers))
# Just list the process.
try:
	conn = SMTP_SSL('smtp.qq.com', port=465)
	conn.login("961950442@qq.com", "Seven1001")
	tolist = ["2307849251@qq.com"]
	try:
		conn.sendmail('961950442@qq.com', tolist, headers.as_string())
	finally:
		conn.quit()
except Exception:
	print("Catch Exception!")
else:
	print("The mail is sending!")