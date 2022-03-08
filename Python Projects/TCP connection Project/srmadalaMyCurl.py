import socket
import csv
import sys
http = input()
http = http.split("//")
if (http[0].split(":")[0] == "https"):
  sys.exit("Error: HTTPS is not supported")
x = False
file = ""

http = http[1].split("/")
if (len(http) == 2):
  if(http[1] != ""):
    file = http[1]

if (" " in file):
  servername = http[1].split(" ")[1]
  file = http[1].split(" ")[0]
  #print(servername)
  x = True

http = http[0].split(":")
if (len(http) != 2):
  port = 80;
else:
  port = int(http[1])

if (x != True):
  servername = http[0]

if ('www' in http[0]):
  try:
    ip = (socket.gethostbyname(http[0]))
  except socket.gaierror:
    print("incorrect ip")
else:
  ip = http[0]

file = ""
#print(ip)
#print(file)

if (file == ""):
  sn = servername
  servername = servername+"\r\n\r\n"
  sentence1 = "GET /" + ' HTTP/1.1\r\nHost: ' + servername
else:
  sentence1 = "GET /" + file + ' HTTP/1.1\r\nHost: ' + servername
#print(sentence1)

hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)

serverName = ip
serverPort = port
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSocket.connect((ip, serverPort))
sentence = sentence1.encode()
clientSocket.sendall(sentence)

try: 
  s1 = clientSocket.recv(1024).decode()
except ConnectionResetError:
  clientSocket.close()
  sys.exit("connection reset error")

status = s1.split("\r")[0].split(" ", 2)
rl = s1.split("r")[0]
#print(rl)
s2 = s1
if (len(s1) >= 1):
  result = status[1]
  message = status[2]
else:
  result = '56'
  message = 'Empty Response'
#print(result)

if port == 443:
  result = '56'
if (result == '200' and port != 443):
  final = "Successful"
  while ("\0" not in s1):
    s1 += clientSocket.recv(1024).decode()
    if ("\r\n\r\n" in s1):
      break;
    
  final_message = s1
  html_object = final_message.split("\r\n\r\n", 1)[1]
  f = open("HTTPoutput.html", "w")
  f.write(html_object)
  #print(final_message)
  #print(html_object)
  print("Success: " + "http://" +sn + "/ " + result + " " + message)

  rows = [ ['Successful or Unsuccessful: ', final], 
         ['Server Status Code: ', result], 
         ['Requested URL: ', sn], 
         ['hostname: ', hostname], 
         ['source IP: ', local_ip], 
         ['destination IP: ', ip],
         ['source port: ', "57617"],
         ['destination port: ', port],
         ['Server Response line: ', "HTTP/1.1 " + result + message]]
else:
  #print(result)
  #print(s1)
  final = "Unsuccessful"
  print("Unsuccessful: " + "http://" +sn + "/ " + result + " " +  message)

  rows = [ ['Successful or Unsuccessful: ', final], 
         ['Server Status Code: ', result], 
         ['Requested URL: ', sn], 
         ['hostname: ', hostname], 
         ['source IP: ', local_ip], 
         ['destination IP: ', ip],
         ['source port: ', "57617"],
         ['destination port: ', port],
         ['Server Response line: ', "HTTP/1.1 " + result + " " + message]]


with open(r'Log', 'a') as f:
    writer = csv.writer(f)
    writer.writerow(rows)
#print(status)
clientSocket.close()