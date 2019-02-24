# coding:utf-8
from ctypes import *
import pyautogui
import os

path=os.path.dirname(os.path.abspath(__file__))
	
dll = windll.LoadLibrary('NekoMacro.dll')
dll.chkimgEX_generate.restype = c_int
dll.chkimgEX_generate.argtypes = [c_char_p,c_float,c_int,c_int,c_int,c_int,c_int,c_void_p,c_void_p,c_void_p,c_int]
dll.chkimgFX_generate.argtypes = [c_char_p,c_int,c_int,c_int,c_int,c_int,c_int,c_void_p,c_void_p,c_int]

G_IMGEX_X = 0
G_IMGEX_Y = 0
G_IMGEX_SCORE = 0
G_IMGEX_NAME =""
ALL_IMGEX_X = [0 for i in range(1000)]
ALL_IMGEX_Y = [0 for i in range(1000)]
ALL_IMGEX_SCORE = [0 for i in range(1000)]

#指定フォルダのフォルダ以外のファイルの全てを|で連結して返す関数
def joinDirImage(dir):
	os.system("dir /a-d /b /s " + dir +" >list.txt")
	imagelist = ""
	with open(path+r"\\list.txt") as f:
		for s_line in f:
			imagelist = imagelist + s_line[:-1] + "|" 
	
	return imagelist[:-1]

#使い方
#chkimgSetImageで指定した画像ファイルとのテンプレートマッチングを行い近似した箇所を探し出します。
#引数説明
#1:画像名
#2:キャプチャしない:-1　キャプチャする場合はsaveimgの仕様に準ずる
#3:一致率
#4:0の場合->テンプレートマッチングを行い、最も近似度の高い箇所を探し出します。複数ある場合左上とは限りません。他の探索より高速です。
# :-1の場合->テンプレートマッチングを行い、指定一致率より高い箇所を左上から全て探し出します。複数ある場合遅くなるので一致率を高めにしてください。
# :1以上の場合->テンプレートマッチングを行い、指定一致率より高い箇所を左上から探し出しますがこの数値以上になったら探索を打ち切ります。
#5:探索範囲の指定x1
#6:探索範囲の指定y1
#7:探索範囲の指定x2
#8:探索範囲の指定y2
#9:1の場合探索結果をディスプレイ表示します。
def chkimgEX(img,captureId = 0, ratio = 0.95, select_num = 0,  rect_ax=0, rect_ay=0, rect_bx=0, rect_by=0,imshow_mode = 0):
	if captureId != -1:
		pyautogui.screenshot(path+r'\\capture.bmp')
		dll.chkimgSetImage((path+r"\\capture.bmp").encode())
 
	global G_IMGEX_X
	global G_IMGEX_Y
	global G_IMGEX_SCORE
	global G_IMGEX_NAME
	
	array = img.split("|")
	
	for _img in array:
		G_IMGEX_X = -999999
		G_IMGEX_Y = -999999
		G_IMGEX_SCORE = 0
		for i in range(1000):
			ALL_IMGEX_X[i] = 0
			ALL_IMGEX_Y[i] = 0
			ALL_IMGEX_SCORE[i] = 0

		IntArray10 = c_int * 100 
		i_arr = [0 for i in range(100)]  
		_img_x = IntArray10(*i_arr)  
		_img_y = IntArray10(*i_arr)
		FloatArray10=c_float*100
		f_arr=[0 for i in range(100)]
		_score = FloatArray10(*f_arr)

		hit_count = dll.chkimgEX_generate(_img.encode(), ratio, select_num,rect_ax, rect_ay, rect_bx, rect_by, byref(_img_x), byref(_img_y), byref(_score),imshow_mode)
		if hit_count > 0:
			G_IMGEX_NAME = os.path.basename(_img)
			break
		if hit_count == -1:
			return -1
 
	if select_num == -1:
		for i in range(hit_count):
			ALL_IMGEX_X[i] = _img_x[i]
			ALL_IMGEX_Y[i] = _img_y[i]
			ALL_IMGEX_Score[i] = _score[i]
		if hit_count > 0:
			G_IMGEX_X=_img_x[hit_count-1]
			G_IMGEX_Y=_img_y[hit_count-1]
		return hit_count

	if hit_count > 0:
		if select_num > 0:
			G_IMGEX_X=_img_x[select_num-1]
			G_IMGEX_Y=_img_y[select_num-1]
			if select_num == hit_count:
				return 1
			else:
				return 0
		else:
			G_IMGEX_X=_img_x[0]
			G_IMGEX_Y=_img_y[0]
			return 1
   
	return 0
 
#使い方
#chkimgSetImageで指定した画像ファイルとの完全一致検索を行いヒットした箇所を探し出します。
#引数説明
#1:画像名
#2:キャプチャしない:-1　キャプチャする場合はsaveimgの仕様に準ずる
#3:探索範囲の指定x1
#4:探索範囲の指定y1
#5:探索範囲の指定x2
#6:探索範囲の指定y2
#7:UWSCの番号指定の仕様に準じます。　
#8:RGBで色幅に範囲をもたせます。16進数で$101010->全ての色に対し16差までは許容します。
#9:1の場合探索結果をディスプレイ表示します。
def chkimgFX(img,captureId=0,rect_ax=0,rect_ay=0,rect_bx=0,rect_by=0,select_num = 0,color_range = 0,imshow_mode = 0):
	if captureId != -1:
		pyautogui.screenshot(path+r'\\capture.bmp')
		dll.chkimgSetImage((path+r"\\capture.bmp").encode())
 
	global G_IMGEX_X
	global G_IMGEX_Y
	global G_IMGEX_NAME
	
	array = img.split("|")
	
	for _img in array:
		G_IMGEX_X = -999999
		G_IMGEX_Y = -999999
		for i in range(1000):
			ALL_IMGEX_X[i] = 0
			ALL_IMGEX_Y[i] = 0

		IntArray10 = c_int * 100 
		i_arr = [0 for i in range(100)]  
		_img_x = IntArray10(*i_arr)  
		_img_y = IntArray10(*i_arr)

		hit_count = dll.chkimgFX_generate(_img.encode(), rect_ax, rect_ay, rect_bx, rect_by,select_num,color_range, byref(_img_x), byref(_img_y),imshow_mode)
		if hit_count > 0:
			G_IMGEX_NAME = os.path.basename(_img)
			break
		if hit_count == -1:
			return -1
 
	if select_num == -1:
		for i in range(hit_count):
			ALL_IMGEX_X[i] = _img_x[i]
			ALL_IMGEX_Y[i] = _img_y[i]
		if hit_count > 0:
			G_IMGEX_X=_img_x[hit_count-1]
			G_IMGEX_Y=_img_y[hit_count-1]
		return hit_count

	if hit_count > 0:
		if select_num > 0:
			G_IMGEX_X=_img_x[select_num-1]
			G_IMGEX_Y=_img_y[select_num-1]
			if select_num == hit_count:
				return 1
			else:
				return 0
		else:
			G_IMGEX_X=_img_x[0]
			G_IMGEX_Y=_img_y[0]
			return 1
	return 0