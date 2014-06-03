#include "queue.h"
#define MIN_PER_HOUR 60

bool newcustomer(double x);

int main(int argc, char **argv){
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ios_base;
    std::srand(std::time(0));
    cout <<"\n\n***************************************\n";
    cout <<"Queue Simulation For Randomized Traffic\n\n\n";
    cout <<"Enter maximum queue size: ";
    int qs;
    cin >> qs;
    Queue line (qs);
    cout <<"Enter simulation hours: ";
    int hours;
    cin >> hours;
    long cyclelimit = MIN_PER_HOUR * hours;
    cout << "Enter average traffic per hour: ";
    double perhour;
    cin >> perhour;
    double min_per_cust;
    min_per_cust = MIN_PER_HOUR;
    Item temp;
    long turnaways = 0;
    long customers = 0;
    long served = 0;
    long sum_line = 0;
    int wait_time = 0;
    long line_wait = 0;

    cout << "\nSimulation running.......\n"<< endl;

    for(int cycle = 0;cycle<cyclelimit; cycle++){
	if(newcustomer(min_per_cust)){
	    if(line.isfull())
		turnaways++;
	    else{
		customers++;
		temp.set(cycle);
		line.enqueue(temp);
	    }
	    if(wait_time <=0 && !line.isempty()){
		line.dequeue (temp);
		wait_time = temp.ptime();
		line_wait += cycle - temp.when();
		served++;
	    }
	    if (wait_time >0)
		wait_time--;
	    sum_line+=line.queuecount();
	}
    }
    if(customers >0){
	cout <<"Customers accepted: "<<customers<<endl;
	cout <<"Customers served: "<<served<<endl;
	cout <<"Customers turnedaway: "<<turnaways<<endl;
	cout <<"Average queue size: ";
	cout.precision(2);
	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.setf(ios_base::showpoint);
	cout << (double) sum_line / cyclelimit << endl;
	cout << "Average wait minutes: " << (double) line_wait / served << endl;
    }
    else
	cout << "No Customers in simulation\n";
    cout << "\nSimulation Ending\n";

    return 0;
}

bool newcustomer(double x){
    return (std::rand() * x/RAND_MAX <1);
}
