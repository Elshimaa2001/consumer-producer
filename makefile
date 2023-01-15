output : main.o main2.o
	g++ producer.o -o producer
	g++ consumer.o -o consumer
	
main.o : producer.cpp
	g++ -c producer.cpp
main2.o : consumer.cpp
	g++ -c consumer.cpp	
	
clean:
	rm *. produce
	rm *. consume
