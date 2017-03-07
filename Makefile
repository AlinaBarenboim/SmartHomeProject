CC = g++ -pthread 

CFLAGS = -g -c -std=gnu++11 -fPIC 

INC_PATH = ./hFiles
SRC_PATH = ./sourseFiles
LOG_PATH = ./logger

.PHONY: clean rebuild 

#//ps ax | grep ./App

OBJC = agent.o event.o eventsHub.o agentFactory.o  App.o agentLifeCicleMng.o configurator.o agentCreator.o  reader.o parser.o configData.o tekenizer_t.o server.o 

App : $(OBJC) 
	$(CC)  -L./logger $(OBJC)  -o App   -ldl  -rdynamic  -llogger

agent.o : $(SRC_PATH)/agent.cpp $(INC_PATH)/agent.h $(INC_PATH)/safeQ.h $(INC_PATH)/event.h $(INC_PATH)/tokenizer_t.h $(LOG_PATH)/inc/logmngr.h $(LOG_PATH)/inc/logmngr.h
	$(CC) $(CFLAGS) $(SRC_PATH)/agent.cpp -pthread 

event.o : $(INC_PATH)/event.h $(SRC_PATH)/event.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)/event.cpp

eventsHub.o : $(INC_PATH)/eventsHub.h $(SRC_PATH)/eventsHub.cpp $(INC_PATH)/event.h $(INC_PATH)/safeQ.h $(INC_PATH)/agent.h
	$(CC) $(CFLAGS) $(SRC_PATH)/eventsHub.cpp

agentFactory.o : $(INC_PATH)/agentFactory.h $(SRC_PATH)/agentFactory.cpp $(INC_PATH)/agentCreator.h $(INC_PATH)/agent.h 
	$(CC) $(CFLAGS) $(SRC_PATH)/agentFactory.cpp

agentCreator.o : $(INC_PATH)/agentCreator.h $(SRC_PATH)/agentCreator.cpp 
	$(CC) $(CFLAGS) $(SRC_PATH)/agentCreator.cpp
	
tekenizer_t.o : $(INC_PATH)/tokenizer_t.h $(SRC_PATH)/tekenizer_t.cpp 
	$(CC) $(CFLAGS) $(SRC_PATH)/tekenizer_t.cpp


agentLifeCicleMng.o : $(INC_PATH)/agentlifeCicleMng.h $(SRC_PATH)/agentLifeCicleMng.cpp $(INC_PATH)/agent.h $(INC_PATH)/agentFactory.h $(INC_PATH)/eventsHub.h $(INC_PATH)/configurator.h $(LOG_PATH)/inc/logmngr.h
	$(CC) $(CFLAGS) $(SRC_PATH)/agentLifeCicleMng.cpp

configurator.o : $(SRC_PATH)/configurator.cpp $(INC_PATH)/configurator.h $(INC_PATH)/reader.h
	$(CC) $(CFLAGS) $(SRC_PATH)/configurator.cpp

App.o : $(SRC_PATH)/App.cpp $(INC_PATH)/App.h $(INC_PATH)/agentFactory.h $(INC_PATH)/reader.h  $(INC_PATH)/elevatorCreator.h  $(LOG_PATH)/inc/logmngr.h 
	$(CC) $(CFLAGS) $(SRC_PATH)/App.cpp  
	
reader.o : $(SRC_PATH)/reader.cpp $(INC_PATH)/reader.h
	$(CC) $(CFLAGS) $(SRC_PATH)/reader.cpp
	
parser.o : $(SRC_PATH)/parser.cpp $(INC_PATH)/parser.h $(INC_PATH)/configData.h
	$(CC) $(CFLAGS) $(SRC_PATH)/parser.cpp
	
configData.o : $(SRC_PATH)/configData.cpp $(INC_PATH)/configData.h
	$(CC) $(CFLAGS) $(SRC_PATH)/configData.cpp
	
server.o : $(SRC_PATH)/server.cpp $(INC_PATH)/server.h
	$(CC) $(CFLAGS) $(SRC_PATH)/server.cpp

# Agent Dynamic Libraries

elevator.o : $(SRC_PATH)/elevator.cpp $(INC_PATH)/elevator.h $(INC_PATH)/agent.h $(INC_PATH)/event.h $(LOG_PATH)/inc/logmngr.h 
	$(CC) $(CFLAGS) $(SRC_PATH)/elevator.cpp -pthread -std=gnu++11 

elevator.so : elevator.o elevatorCreator.o 
	$(CC) elevator.o elevatorCreator.o  -o elevator.so  -shared 
	
	
elevatorCreator.o : $(INC_PATH)/elevatorCreator.h $(SRC_PATH)/elevatorCreator.cpp  $(INC_PATH)/configurator.h $(INC_PATH)/agentCreator.h  $(INC_PATH)/eventsHub.h  $(INC_PATH)/configData.h  $(INC_PATH)/elevator.h
	$(CC) $(CFLAGS) $(SRC_PATH)/elevatorCreator.cpp
	
	
liveLog.o : $(SRC_PATH)/liveLog.cpp $(INC_PATH)/liveLog.h $(INC_PATH)/agent.h $(INC_PATH)/event.h $(INC_PATH)/server.h $(LOG_PATH)/inc/logmngr.h
	$(CC) $(CFLAGS) $(SRC_PATH)/liveLog.cpp -pthread -std=gnu++11	
	
liveLogCreator.o : $(INC_PATH)/liveLogCreator.h $(SRC_PATH)/liveLogCreator.cpp  $(INC_PATH)/configurator.h $(INC_PATH)/agentCreator.h  $(INC_PATH)/eventsHub.h  $(INC_PATH)/configData.h  
	$(CC) $(CFLAGS) $(SRC_PATH)/liveLogCreator.cpp
	
liveLog.so : liveLog.o liveLogCreator.o 
	$(CC) liveLog.o liveLogCreator.o  -o liveLog.so  -shared 
 
	
#elevatorCreator.so : elevatorCreator.o 
#	$(CC) elevatorCreator.o -o elevatorCreator.so -shared 


temp_sensor.o : $(SRC_PATH)/temp_sensor.cpp $(INC_PATH)/temp_sensor.h $(INC_PATH)/agent.h $(INC_PATH)/event.h $(LOG_PATH)/inc/logmngr.h
	$(CC) $(CFLAGS) $(SRC_PATH)/temp_sensor.cpp -pthread -std=gnu++11	
	
tempSensorCreator.o : $(INC_PATH)/tempSensorCreator.h $(SRC_PATH)/tempSensorCreator.cpp  $(INC_PATH)/configurator.h $(INC_PATH)/agentCreator.h  $(INC_PATH)/eventsHub.h  $(INC_PATH)/configData.h  
	$(CC) $(CFLAGS) $(SRC_PATH)/tempSensorCreator.cpp
	
temp_sensor.so : temp_sensor.o tempSensorCreator.o 
	$(CC) temp_sensor.o tempSensorCreator.o  -o temp_sensor.so  -shared 
#*********************************************************************************
	
hvac.o : $(SRC_PATH)/hvac.cpp $(INC_PATH)/hvac.h $(INC_PATH)/agent.h $(INC_PATH)/event.h $(LOG_PATH)/inc/logmngr.h
	$(CC) $(CFLAGS) $(SRC_PATH)/hvac.cpp -pthread -std=gnu++11	
	
hvacCreator.o : $(INC_PATH)/hvacCreator.h $(SRC_PATH)/hvacCreator.cpp  $(INC_PATH)/configurator.h $(INC_PATH)/agentCreator.h  $(INC_PATH)/eventsHub.h  $(INC_PATH)/configData.h  
	$(CC) $(CFLAGS) $(SRC_PATH)/hvacCreator.cpp
	
hvac.so : hvac.o hvacCreator.o 
	$(CC) hvac.o hvacCreator.o  -o hvac.so  -shared 
	
	



fire_sensor.o : $(SRC_PATH)/fire_sensor.cpp $(INC_PATH)/fire_sensor.h $(INC_PATH)/agent.h $(INC_PATH)/event.h $(LOG_PATH)/inc/logmngr.h
	$(CC) $(CFLAGS) $(SRC_PATH)/fire_sensor.cpp -pthread -std=gnu++11
	
fireSensorCreator.o : $(INC_PATH)/fireSensorCreator.h $(SRC_PATH)/fireSensorCreator.cpp  $(INC_PATH)/configurator.h $(INC_PATH)/agentCreator.h  $(INC_PATH)/eventsHub.h  $(INC_PATH)/configData.h  
	$(CC) $(CFLAGS) $(SRC_PATH)/fireSensorCreator.cpp
	
fire_sensor.so : fire_sensor.o fireSensorCreator.o 
	$(CC) fire_sensor.o fireSensorCreator.o  -o fire_sensor.so  -shared 
	
	
sprinkler_controller.o : $(SRC_PATH)/sprinkler_controller.cpp $(INC_PATH)/sprinkler_controller.h $(INC_PATH)/agent.h $(INC_PATH)/event.h $(LOG_PATH)/inc/logmngr.h
	$(CC) $(CFLAGS) $(SRC_PATH)/sprinkler_controller.cpp -pthread -std=gnu++11
	
sprinklerControllerCreator.o : $(INC_PATH)/sprinklerControllerCreator.h $(SRC_PATH)/sprinklerControllerCreator.cpp  $(INC_PATH)/configurator.h $(INC_PATH)/agentCreator.h  $(INC_PATH)/eventsHub.h  $(INC_PATH)/configData.h  
	$(CC) $(CFLAGS) $(SRC_PATH)/sprinklerControllerCreator.cpp
	
sprinkler_controller.so : sprinkler_controller.o sprinklerControllerCreator.o 
	$(CC) sprinklerControllerCreator.o sprinkler_controller.o  -o sprinkler_controller.so  -shared 

clean:
	rm -f *.o
	rm -f App
	
rebuild: clean App fire_sensor.so hvac.so temp_sensor.so liveLog.so elevator.so sprinkler_controller.so
 


