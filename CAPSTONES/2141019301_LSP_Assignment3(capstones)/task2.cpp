#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;
struct CPUData{
	long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
};
CPUData getCPUData(){
	ifstream file("/proc/stat");
	string line;
	CPUData cpu={};
	if (file.is_open()){
		getline(file,line);
		istringstream ss(line);
		string cpuLabel;
		ss >> cpuLabel >> cpu.user >> cpu.nice >> cpu.system >> cpu.idle >> cpu.iowait >> cpu.irq >> cpu.softirq >> cpu.steal >> cpu.guest >> cpu.guest_nice;
	}
	return cpu;
}
double calculateCPUUsage (CPUData prev, CPUData current){
	long prevIdle= prev.idle + prev.iowait;
	long currIdle= current.idle + current.iowait;
	long prevTotal = prev.user + prev.nice + prev.system + prev.idle + prev.iowait + prev.irq + prev.softirq + prev.steal;
	long currTotal = current.user + current.nice + current.system + current.idle + current.iowait + current.irq + current.softirq + current.steal;
	long totalDiff = currTotal - prevTotal;
	long idleDiff = currIdle - prevIdle;
	return ((totalDiff - idleDiff) * 100.0) / totalDiff;
}
int main(){
	CPUData cpu= getCPUData();
	cout << "User: " << cpu.user << endl;
    cout << "Nice: " << cpu.nice << endl;
    cout << "System: " << cpu.system << endl;
    cout << "Idle: " << cpu.idle << endl;
    cout << "IOwait: " << cpu.iowait << endl;
    cout << "IRQ: " << cpu.irq << endl;
    cout << "SoftIRQ: " << cpu.softirq << endl;
    cout << "Steal: " << cpu.steal << endl;
    cout << "Guest: " << cpu.guest << endl;
    cout << "Guest Nice: " << cpu.guest_nice << endl;
    CPUData prevData = getCPUData();
    this_thread::sleep_for(chrono::seconds(1));
    CPUData currData = getCPUData();
    double cpuUsage= calculateCPUUsage (prevData, currData);
    cout << "CPU Usage: "<<cpuUsage<<endl;
	return 0;
}

