import pygame
import math
from pygame.locals import *
from sys import exit
pygame.init()

WIDTH = 600
HEIGHT = 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
WHITE = (255,255,255)
BLACK = (0,0,0)

r1 = 80 #radius 2D circle
r2 = 100 #distance from center / radius torus
A, B = 0, 0 #rotation angles x- and z-axis
K2=5000
K1=WIDTH*K2*3/(8*(r1+r2))
term = 10
pm = math.floor(r1*100/term) #math.floor(r1*100/6)
x_offset = WIDTH / 2
y_offset = HEIGHT / 2
uping=1
downing=0

def draw(x, y):
    pygame.draw.circle(screen, WHITE, (x + x_offset, y + y_offset), 1)

while True:
    screen.fill((BLACK)) #erase previous donut
    cosB, sinB = math.cos(B), math.sin(B)
    cosA, sinA = math.cos(A), math.sin(A)
    
    for P in range(0,628,15):
        for deltax in range(0,r1*100,pm):
            x2 = deltax / 100
            y2 = -x2+r1 - 6
            cosP, sinP = math.cos(P/100), math.sin(P/100)
            x = x2*(cosB*cosP+sinA*sinB*sinP)-y2*cosA*sinB
            y = y2*cosA*cosB+x2*(cosP*sinB-sinA*sinP*cosB)
            z = cosA*x2*sinP+K2
            ooz = 1/z

            xp = math.floor(x*K1*ooz)
            yp = math.floor(-y*K1*ooz)
            draw(xp, yp)
        for deltax in range(0,r1*100,pm):
            x2 = deltax / 100
            y2 = x2-r1 + 6
            cosP, sinP = math.cos(P/100), math.sin(P/100)
            x = x2 *(cosB*cosP+sinA*sinB*sinP)-y2*cosA*sinB
            y = y2*cosA*cosB+x2*(cosP*sinB-sinA*sinP*cosB)
            z = cosA*x2*sinP+K2
            ooz = 1/z

            xp = math.floor(x*K1*ooz)
            yp = math.floor(-y*K1*ooz)
            draw(xp, yp)
    if A != 2:
        A += 0.001 #0.001
        B += 0.0005 #0.0005
    else:
        A = 0
        B = 0
    if downing==1:
        K2-=10
    elif uping==1:
        K2+=10
    if uping==1 and K2>10000:
        uping=0
        downing=1
    elif downing==1 and K2<5000:
        uping=1
        downing=0
    for event in pygame.event.get(): #close window when close button is pressed
        if event.type == QUIT:
            exit()

    pygame.display.update() #display changes