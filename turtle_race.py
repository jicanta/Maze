import turtle, sys, time, random

WIDTH, HEIGHT = 500, 500
COLORS = ['red', 'green', 'blue', 'yellow', 'purple', 'black', 'pink', 'brown', 'orange', 'cyan']

n = int(input('Enter the number of turtle racers (2-10): '))

screen = turtle.Screen()
screen.setup(WIDTH, HEIGHT)
screen.title('Turtle Race!')

finishLine = turtle.Turtle()
finishLine.penup()
finishLine.color('black')
finishLine.hideturtle()
finishLine.speed(0)
finishLine.setpos(-WIDTH // 2, -70 + HEIGHT // 2)
finishLine.pendown()
finishLine.forward(WIDTH)

random.shuffle(COLORS)

racers = []
spacing = WIDTH // (n + 1)

for i in range (n):
    racer = turtle.Turtle()
    racer.color(COLORS[i])
    racer.left(90)
    racer.shape('turtle')
    racer.penup()
    racer.setpos(spacing * (i + 1) - WIDTH // 2, 15 - HEIGHT // 2)
    racer.pendown()
    racers.append(racer)

bet = str(input('Which color are you betting for? '))
time.sleep(5)

while True:
    for racer in racers:
        dist = random.randrange(1, 30)
        racer.forward(dist)
        x, y = racer.pos()
        if y >= -70 + HEIGHT // 2:
            color = COLORS[racers.index(racer)]
            if color == bet:
                print(f'Congratulations, {bet} won!')
            else:
                print(f'{color} won! Good luck next time!')
            sys.exit()
