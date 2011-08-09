
TARGET					:=	LegendsRun.exe
CODE_FILES				:=	Main.cpp

Default:
	g++ $(CODE_FILES) -DCURL_STATICLIB `curl-config --cflags --static-libs` --static -o $(TARGET) -Os
	
	