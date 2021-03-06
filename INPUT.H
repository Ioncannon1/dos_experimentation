#ifndef INC_INPUT_H
#define INC_INPUT_H

#define JOYSTICK_PORT 0x201

#define JOYA_POSX 0x1
#define JOYA_POSY 0x2
#define JOYB_POSX 0x4
#define JOYB_POSY 0x8
#define JOYA_BUTTON1 0x10
#define JOYA_BUTTON2 0x20
#define JOYB_BUTTON1 0x40
#define JOYB_BUTTON2 0x80

#define JOYSTICK_NORMAL_VALUE 255

#define MOUSE_BUTTON1 0x01
#define MOUSE_BUTTON2 0x02
#define MOUSE_BUTTON3 0x03

extern unsigned int getJoystickPosition(unsigned char);
extern unsigned char getJoystickButtons();

extern unsigned char resetMouse();
extern void setMouseXBounds(unsigned int x, unsigned int y);
extern void setMouseXBounds(unsigned int x, unsigned int y);
extern void getMouseState(unsigned int *, unsigned int *, unsigned char *);

extern unsigned char getModKeys();
extern unsigned char getKeyCode();

#endif