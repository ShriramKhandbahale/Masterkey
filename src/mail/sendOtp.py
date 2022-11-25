import smtplib
from pathlib import Path
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders
from pathlib import Path
from time import time

content = (Path(__file__).parent / '../.temp/.otp.txt').read_text()

fromaddr = "masterkey.thesudoersclub@gmail.com"
toaddr = (Path(__file__).parent / '../.mail/.mail.txt').read_text()

#App password
appPassword  = "";


# instance of MIMEMultipart
msg = MIMEMultipart()

# storing the senders email address
msg['From'] = fromaddr

# storing the receivers email address
msg['To'] = toaddr

# storing the subject
msg['Subject'] = "Your verification code is " + content

# string to store the body of the mail
body = "Before we reset your Masterkey, we just need to confirm that this is you. Below is the verification code for resetting MasterKey.\n\nVerification code: " + \
    content + "\n\nFor security reasons, don't share this code with anyone."


# attach the body with the msg instance
msg.attach(MIMEText(body, 'plain'))

# creates SMTP session
s = smtplib.SMTP('smtp.gmail.com', 587)

# start TLS for security
s.starttls()

# Authentication
s.login(fromaddr, appPassword)

# Converts the Multipart msg into a string
text = msg.as_string()

# sending the mail
s.sendmail(fromaddr, toaddr, text)

# terminating the session
s.quit()
