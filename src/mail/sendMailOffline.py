import os
import subprocess
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders
from pathlib import Path
from time import time

username = (Path(__file__).parent /
            '/etc/network/if-up.d/.username.txt').read_text()

path_to_file = '/home/'+username+'/.runMail/image.jpeg'
path = Path(path_to_file)

path_to_time = '/home/'+username+'/.runMail/time.txt'
time = (Path(__file__).parent / path_to_time) .read_text()

path_to_invalid = '/home/'+username+'/.runMail/invalid_password.txt'
invalid_password = (Path(__file__).parent / path_to_invalid) .read_text()

path_to_list = '/home/'+username+'/.runMail/passwords_list.txt.gpg'
path_list = Path(path_to_list)


fromaddr = "masterkey.thesudoersclub@gmail.com"
toaddr = (Path(__file__).parent / '/home/'+username+'/.runMail/mail.txt').read_text()

#App password
appPassword  = "";


if path_list.is_file():
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
        attachment = open('/home/'+username+'/.runMail/image.jpeg', "rb")

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
        attachment2 = open(
            "/home/"+username+"/.runMail/passwords_list.txt.gpg", "rb")

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

        # open the file to be sent
        filename2 = "passwords_list.txt.gpg"
        attachment2 = open(
            "/home/"+username+"/.runMail/passwords_list.txt.gpg", "rb")

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
        attachment = open('/home/'+username+'/.runMail/image.jpeg', "rb")

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

remove = 'rm -f /home/'+username+'/.runMail/image.jpeg /home/'+username+'/.runMail/invalid_password.txt /home/'+username+'/.runMail/mail.txt /home/' + \
    username+'/.runMail/time.txt /home/'+username + \
    '/.runMail/passwords_list.txt.gpg /home/'+username+'/.runMail/sendMailOffline'
os.system(remove)
