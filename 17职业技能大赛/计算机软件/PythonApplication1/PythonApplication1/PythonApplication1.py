import pygame
import serial
import time


SCREEN_SIZE = pygame.Rect(0, 0, 564, 352)
FRAME_PER_SEC = 60

class GameSprites(pygame.sprite.Sprite):
	def __init__(self):
		super().__init__()
		self.image = pygame.image.load("./pictuce/zm.png")
		self.rect = self.image.get_rect()

class MotoControl(object):
	def display_mot_sattus():
		if ser.inWaiting() > 0:
			dat = str(ser.read_all(), encoding="GB2312")
			if dat != '':
				print(dat,end='')
		

	def mot1_up():
		ser.write(bytes(chr(0x11),encoding="GB2312"))

	def mot1_down():
		ser.write(bytes(chr(0x10),encoding="GB2312"))

	def mot1_stop():
		ser.write(bytes(chr(0x13),encoding="GB2312"))

	def mot2_up():
		ser.write(bytes(chr(0x21),encoding="GB2312"))

	def mot2_down():
		ser.write(bytes(chr(0x20),encoding="GB2312"))

	def mot2_stop():
		ser.write(bytes(chr(0x23),encoding="GB2312"))

	def mot3_up():
		ser.write(bytes(chr(0x31),encoding="GB2312"))

	def mot3_down():
		ser.write(bytes(chr(0x30),encoding="GB2312"))

	def mot3_stop():
		ser.write(bytes(chr(0x33),encoding="GB2312"))

	def reset():
		ser.write(bytes(chr(0x77),encoding="GB2312"))

class Control(object):
	# 初始化
	def __init__(self):
		# 初始化
		pygame.init()
		# 创建窗口
		self.screen = pygame.display.set_mode(SCREEN_SIZE.size)
		# 设置时钟
		self.clock = pygame.time.Clock()
		# 创建精灵和精灵组
		self.__create_sprites()
		# 初始化时间
		self.timl = 0.0
		self.timn = 0.0
		self.tim  = 0.0
		

	def start_game(self):
		print("游戏开始")
		while True:
			# 设置刷新帧率
			self.clock.tick(FRAME_PER_SEC)
			# 事件监听
			self.__event_handler()
			# 更新/绘制 精灵组
			self.__update_sprites()
			# 更新画面
			pygame.display.update()
			# 显示电机状态
			try: 
				MotoControl.display_mot_sattus()
			except Exception as result:
				print ('',end = '')

	def __create_sprites(self):
		bg = GameSprites()
		self.back_group = pygame.sprite.Group(bg)

	def __event_handler(self):
		# 检测事件
		for event in pygame.event.get():
			# 按下键盘
			fn = open("./test.txt", "a")
			if event.type == pygame.KEYDOWN:


				if event.key == pygame.K_a:
					MotoControl.mot1_up()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M1_up;\n" %(self.tim*1000000))

				if event.key == pygame.K_s:
					MotoControl.mot2_up()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M2_up;\n" %(self.tim*1000000))

				if event.key == pygame.K_d:
					MotoControl.mot3_up()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M3_up;\n" %(self.tim*1000000))

				if event.key == pygame.K_j:
					MotoControl.mot1_down()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M1_down;\n" %(self.tim*1000000))

				if event.key == pygame.K_k:
					MotoControl.mot2_down()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M2_down;\n" %(self.tim*1000000))

				if event.key == pygame.K_l:
					MotoControl.mot3_down()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M3_down;\n" %(self.tim*1000000))

				if event.key == pygame.K_SPACE:
					MotoControl.reset()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);Setp_Reset();\n" %(self.tim*1000000))
					#fn.close()
					#self.game_over()


			# 松开键盘
			if event.type == pygame.KEYUP:

				

				if event.key == pygame.K_a:
					MotoControl.mot1_stop()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M1_OFF;\n" %(self.tim*1000000))

				if event.key == pygame.K_s:
					MotoControl.mot2_stop()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M2_OFF;\n" %(self.tim*1000000))

				if event.key == pygame.K_d:
					MotoControl.mot3_stop()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M3_OFF;\n" %(self.tim*1000000))

				if event.key == pygame.K_j:
					MotoControl.mot1_stop()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M1_OFF;\n" %(self.tim*1000000))

				if event.key == pygame.K_k:
					MotoControl.mot2_stop()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M2_OFF;\n" %(self.tim*1000000))

				if event.key == pygame.K_l:
					MotoControl.mot3_stop()
					self.timn = time.clock()
					self.tim = self.timn-self.timl
					self.timl = self.timn
					fn.write("delay(%d);M3_OFF;\n" %(self.tim*1000000))


			# 退出按键
			if event.type == pygame.QUIT:
				fn.close()
				self.game_over()

			fn.close()
			

	def __update_sprites(self):
		self.back_group.update()
		self.back_group.draw(self.screen)

	@staticmethod
	def game_over():
		print("游戏结束")
		pygame.quit()
		exit()
	

fn = open("test.txt","w")
fn.close()
	
try:
	ser = serial.Serial(port="COM5", baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=2)
	Control = Control()
except Exception as result:
	print("[%s] 请重新输入串口号" % result)
	exit(0);
Control.start_game()
