import sys
import struct
import termios

def func1(x, y):
    print "%d+%d = %d" %(x, y, x+y)
def func2(x, y):
    print "%d-%d = %d" %(x, y, x-y)
def func3(x, y):
    print "%d*%d = %d" %(x, y, x*y)

funcdict = {
        "func1": func1,
        "func2": func2,
        "func3": func3,
        }

menu = [
        #(index, id, function name, function ptr)
        ("0", '0', "Exit", "NULL"),
        ("1", '1', "Func#1", "func1"),
        ("a", 'a', "Func#2", "func2"),
        ("^U", '\x15', "Func#3", "func3"),
       ]

init_setting = termios.tcgetattr(sys.stdin.fileno())
new_setting = termios.tcgetattr(sys.stdin.fileno())

new_setting[3] &= ~termios.ICANON
new_setting[3] &= ~termios.ECHO
new_setting[6][termios.VTIME] = 0
new_setting[6][termios.VMIN] = 1

while True:
    for i in range(len(menu)):
        print "[%s]:\t%s." %(menu[i][0], menu[i][2])

    termios.tcsetattr(sys.stdin.fileno(), termios.TCSAFLUSH, new_setting)
    opt = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin.fileno(), termios.TCSANOW, init_setting)

    for i in range(len(menu)):
        if opt == menu[i][1]:
            if menu[i][3] == "NULL":
                sys.exit()
            else:
                funcdict[menu[i][3]](3, 2)

