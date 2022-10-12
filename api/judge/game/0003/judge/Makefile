TARGET = judge.exe
COMPILER = g++ -std=c++11 -O2

target : $(TARGET)

main.o : logic/main.cpp
	$(COMPILER) -c logic/main.cpp -o main.o

#Mkdir.o : logic/Mkdir.c
#	$(COMPILER) -c logic/Mkdir.c -o Mkdir.o

# ai.o : logic/ai.cpp
# 	$(COMPILER) -c logic/ai.cpp -o ai.o

# ai_infinityloop.o : logic/ai_infinityloop.cpp
# 	$(COMPILER) -c logic/ai_infinityloop.cpp -o ai_infinityloop.o

# ai_pc.o : logic/ai_pc.cpp
# 	$(COMPILER) -c logic/ai_pc.cpp -o ai_pc.o

# ai_sxy.o : logic/ai_sxy.cpp
# 	$(COMPILER) -c logic/ai_sxy.cpp -o ai_sxy.o

# ai_test.o : logic/ai_test.cpp
# 	$(COMPILER) -c logic/ai_test.cpp -o ai_test.o

# ai_yjc.o : logic/ai_yjc.cpp
# 	$(COMPILER) -c logic/ai_yjc.cpp -o ai_yjc.o

Camp.o : logic/Camp.cpp
	$(COMPILER) -c logic/Camp.cpp -o Camp.o

# M.o : logic/M.cpp
# 	$(COMPILER) -c logic/M.cpp -o M.o

player_code.o : logic/player_code.cpp
	$(COMPILER) -c logic/player_code.cpp -o player_code.o

json_value.o : lib_json/json_value.cpp
	$(COMPILER) -c lib_json/json_value.cpp -o json_value.o

json_writer.o : lib_json/json_writer.cpp
	$(COMPILER) -c lib_json/json_writer.cpp -o json_writer.o

json_reader.o : lib_json/json_reader.cpp
	$(COMPILER) -c lib_json/json_reader.cpp -o json_reader.o

$(TARGET) : main.o Camp.o player_code.o json_value.o json_writer.o json_reader.o
	$(COMPILER) -o $(TARGET) main.o Camp.o player_code.o json_value.o json_writer.o json_reader.o

clean : 
	rm -f $(TARGET) main.o Camp.o player_code.o json_value.o json_writer.o json_reader.o
