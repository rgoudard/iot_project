import sys
from ftplib import FTP
from os import remove

print(len(sys.argv))
path = sys.argv[1]
if len(sys.argv) >= 3:
    name = sys.argv[2]
else:
    name = "test.JPG"

if len(sys.argv) >= 4:
    host = sys.argv[3]
else:
    host = "HOST"

if len(sys.argv) >= 5:
    user = sys.argv[4]
else:
    user = "USER"

if len(sys.argv) >= 6:
    password = sys.argv[5]
else:
    password = "PASSWORD"

if len(sys.argv) >= 7:
    destination = sys.argv[6]
else:
    destination = "DESTINATION_PATH"

print(path)

ftp = FTP(host)
ftp.login(user, password)
print("connection OK")
ftp.cwd(destination)
print("start upload of " + name)
ftp.storbinary("STOR " + name, open(path, 'rb'))
print("upload OK")
remove(path)
print("temp file deleted")