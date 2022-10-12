TARGET = judge.exe
COMPILER = g++ -std=c++11 -O2

target : $(TARGET)

main.o : logic/main.cpp
	$(COMPILER) -c logic/main.cpp -o main.o

controller.o : controller/Controller.cpp
	$(COMPILER) -c controller/Controller.cpp -o controller.o

game.o : logic/game.cpp
	$(COMPILER) -c logic/game.cpp -o game.o

player_code.o : logic/player_code.cpp
	$(COMPILER) -c logic/player_code.cpp -o player_code.o

player.o : logic/player.cpp
	$(COMPILER) -c logic/player.cpp -o player.o

tower.o : logic/tower.cpp
	$(COMPILER) -c logic/tower.cpp -o tower.o

map.o : logic/map.cpp
	$(COMPILER) -c logic/map.cpp -o map.o

Crops.o : logic/Crops.cpp
	$(COMPILER) -c logic/Crops.cpp -o Crops.o

definition.o : logic/definition.cpp
	$(COMPILER) -c logic/definition.cpp -o definition.o

json_value.o : lib_json/json_value.cpp
	$(COMPILER) -c lib_json/json_value.cpp -o json_value.o

json_writer.o : lib_json/json_writer.cpp
	$(COMPILER) -c lib_json/json_writer.cpp -o json_writer.o

json_reader.o : lib_json/json_reader.cpp
	$(COMPILER) -c lib_json/json_reader.cpp -o json_reader.o

$(TARGET) : main.o controller.o game.o player_code.o player.o tower.o map.o Crops.o json_value.o json_writer.o json_reader.o definition.o
	$(COMPILER) -o $(TARGET) main.o controller.o game.o player_code.o player.o tower.o map.o Crops.o json_value.o json_writer.o json_reader.o definition.o

clean : 
	rm -f $(TARGET) main.o controller.o game.o player_code.o player.o tower.o map.o Crops.o json_value.o json_writer.o json_reader.o definition.o
