import pygame
import sys
import json

if( len(sys.argv) != 2 ):
    print("usage: draw_obst.py <outupt filename>")
    exit(-1)

out_file = sys.argv[1];

obstacles_static = [ {"x":0, "y":0, "w":5, "h":5},
                     {"x":780, "y":0, "w":5, "h":5},
                     {"x":780, "y":780, "w":5, "h":5},
                     {"x":0, "y":780, "w":5, "h":5} ]
obstacles_dynamic = []

WIDTH, HEIGHT = 800, 800

pygame.init()
screen = pygame.display.set_mode( (WIDTH, HEIGHT) )
done = False
mode = "none"
pressed_x = 0;
pressed_y = 0;

while not done:
        for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    done = True

                if event.type == pygame.KEYDOWN:

                    if event.key == pygame.K_s:
                        mode = "static"
                        print("static: press and drag");

                    if event.key == pygame.K_d:
                        mode = "dynamic"
                        print("dynamic: press and drag");

                    if event.key == pygame.K_RETURN:
                        json_out = {}
                        json_out["static"] = obstacles_static;
                        json_out["dynamic"] = obstacles_dynamic;
                        json_out = json.dumps(json_out)
                        print("saving to: " + out_file )
                        print( json_out )
                        f = open(out_file, "a")
                        f.write(json_out)
                        f.close()


                if event.type == pygame.MOUSEBUTTONDOWN:
                    mousex, mousey = pygame.mouse.get_pos()
                    pressed_x = mousex;
                    pressed_y = mousey;
                    print("pressed")

                if event.type == pygame.MOUSEBUTTONUP:
                    mousex, mousey = pygame.mouse.get_pos()
                    new_obst = { "x":pressed_x,
                                 "y":pressed_y,
                                 "w":mousex - pressed_x,
                                 "h":mousey - pressed_y }

                    if mode == "static":
                        obstacles_static.append(new_obst);
                    elif mode == "dynamic":
                        obstacles_dynamic.append(new_obst);

                    mode = "none"
                    print("released")


        screen.fill((255, 255, 255))

        for obst in obstacles_static:
            pygame.draw.rect( screen,
                              (0, 0, 0),
                              pygame.Rect(obst["x"], obst["y"], obst["w"], obst["h"]))

        for obst in obstacles_dynamic:
            pygame.draw.rect( screen,
                              (100, 100, 100),
                              pygame.Rect(obst["x"], obst["y"], obst["w"], obst["h"]))

        pygame.display.flip()
