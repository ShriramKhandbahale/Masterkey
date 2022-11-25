import os
import subprocess
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders
from pathlib import Path
from time import time

path_to_file = '../.temp/.image.jpeg'
path = Path(path_to_file)

time = (Path(__file__).parent / '../.temp/.time.txt').read_text()
invalid_password = (Path(__file__).parent /
                    '../.data/.invalid_password.txt').read_text()

fromaddr = "masterkey.thesudoersclub@gmail.com"

toaddr = (Path(__file__).parent / '../.mail/.mail.txt').read_text()

#App password
appPassword  = "";


limit = (Path(__file__).parent / '../.temp/.limit.txt').read_text()
limit = int(limit)

if limit == 3:
    if path.is_file():
        # instance of MIMEMultipart
        msg = MIMEMultipart()

        # storing the senders email address
        msg['From'] = fromaddr

        # storing the receivers email address
        msg['To'] = toaddr

        # storing the subject
        msg['Subject'] = "Security alert | MasterKey backup"

        # string to store the body of the mail
        body = "There was an invalid login attempt on " + time + \
            "\nPassword tried: "+invalid_password + \
            "\n\n--------------------\n\nTaking security precautions, \"passwords_list.txt\" was removed from the system.\nPlease refer to the attached file to import the list again."

        # attach the body with the msg instance
        msg.attach(MIMEText(body, 'plain'))

        # open the file to be sent
        filename = "image.jpeg"
        attachment = open("../.temp/.image.jpeg", "rb")

        # instance of MIMEBase and named as p
        p = MIMEBase('application', 'octet-stream')

        # To change the payload into encoded form
        p.set_payload((attachment).read())

        # encode into base64
        encoders.encode_base64(p)

        p.add_header('Content-Disposition',
                     "attachment; filename= %s" % filename)

        # attach the instance 'p' to instance 'msg'
        msg.attach(p)

        # open the file to be sent
        filename2 = "passwords_list.txt.gpg"
        attachment2 = open("/home/ayush/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt.gpg", "rb")

        # instance of MIMEBase and named as p
        p2 = MIMEBase('application', 'octet-stream')

        # To change the payload into encoded form
        p2.set_payload((attachment2).read())

        # encode into base64
        encoders.encode_base64(p2)

        p2.add_header('Content-Disposition',"attachment; filename= %s" % filename2)

        # attach the instance 'p' to instance 'msg'
        msg.attach(p2)

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
    else:
        # instance of MIMEMultipart
        msg = MIMEMultipart()

        # storing the senders email address
        msg['From'] = fromaddr

        # storing the receivers email address
        msg['To'] = toaddr

        # storing the subject
        msg['Subject'] = "Security alert | MasterKey"

        # string to store the body of the mail
        body = "There was an invalid login attempt on " + time + "\nPassword tried: "+invalid_password + \
            "\n\nImage not available.\nYou might not have a camera configured to your system.\n\n--------------------\n\nTaking security precautions, \"passwords_list.txt\" was removed from the system.\nPlease refer to the attached file to import the list again."

        # attach the body with the msg instance
        msg.attach(MIMEText(body, 'plain'))

        # open the file to be sent
        filename2 = "passwords_list.txt.gpg"
        attachment2 = open("../.data/.passwords_list.txt.gpg", "rb")

        # instance of MIMEBase and named as p
        p2 = MIMEBase('application', 'octet-stream')

        # To change the payload into encoded form
        p2.set_payload((attachment2).read())

        # encode into base64
        encoders.encode_base64(p2)

        p2.add_header('Content-Disposition',
                      "attachment; filename= %s" % filename2)

        # attach the instance 'p' to instance 'msg'
        msg.attach(p2)

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

    os.system(
        "rm -f /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt.gpg")
else:
    if path.is_file():
        # instance of MIMEMultipart
        msg = MIMEMultipart()

        # storing the senders email address
        msg['From'] = fromaddr

        # storing the receivers email address
        msg['To'] = toaddr

        # storing the subject
        msg['Subject'] = "Security alert"

        # string to store the body of the mail
        body = "There was an invalid login attempt on " + time + \
            "\nPassword tried: "+invalid_password + \
            "\n\nIf that was you, ignore this message else take the necessary actions."

        # attach the body with the msg instance
        msg.attach(MIMEText(body, 'plain'))

        # open the file to be sent
        filename = "image.jpeg"
        attachment = open("../.temp/.image.jpeg", "rb")

        # instance of MIMEBase and named as p
        p = MIMEBase('application', 'octet-stream')

        # To change the payload into encoded form
        p.set_payload((attachment).read())

        # encode into base64
        encoders.encode_base64(p)

        p.add_header('Content-Disposition',
                     "attachment; filename= %s" % filename)

        # attach the instance 'p' to instance 'msg'
        msg.attach(p)

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
    else:
        # instance of MIMEMultipart
        msg = MIMEMultipart()

        # storing the senders email address
        msg['From'] = fromaddr

        # storing the receivers email address
        msg['To'] = toaddr

        # storing the subject
        msg['Subject'] = "Security alert"

        # string to store the body of the mail
        body = "There was an invalid login attempt on " + time + "\nPassword tried: "+invalid_password + \
            "\n\nIf that was you, ignore this message else take the necessary actions.\n\nImage not available.\nYou might not have a camera configured to your system."

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
