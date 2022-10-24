//
// Created by Zhe Chen on 10/6/20.
//
#include <iostream>
#include <fstream>

#include <boost/program_options.hpp>
#include "Agent.h"
#include "agents_loader.h"
#include "Task.h"
#include "TaskAssignment.h"
#include "ICBSSearch.h"
#include "CBSHOnline.h"
#include "PathPlanning.h"
#include "map_loader_with_cost.h"
#include "TaskAssignmentPP.h"
#include "TaskAssignmentRegret.h"
#include "TaskAssignmentTaskHeap.h"
#include "TaskAssignmentTaskHeapRegret.h"
#include "TaskAssignmentRegretTask.h"
#include "TaskAssignmentPPTask.h"
#include "online_simu.h"
int map_cols=0;
int screen = 1;
/*
./MAPD 
-m kiva-20-500-5.map 
-a kiva-20-500-5.map 
-t 0.task 
--capacity 1 
-o output_PP_2.txt 

./MAPD -m kiva-20-500-5.map -a kiva-20-500-5.map -t 0.task --capacity 1 -o output_PP_2.txt 
*/
int main(int argc, char** argv){
    namespace po = boost::program_options;

    //Leggo l'input da comando
    po::options_description desc("Allowed options");
    desc.add_options()
        ("map,m", po::value<std::string>()->required(), "input file for map")
        ("agents,a", po::value<std::string>()->required(), "initial locations for agents")
        ("tasks,t", po::value<std::string>()->required(), "a set of tasks")
        ("output,o", po::value<std::string>()->required(), "output file for schedule")
        ("capacity", po::value<int>()->default_value(1), "cutoff time (seconds)");

    po::variables_map temp;
    po::store(po::parse_command_line(argc, argv, desc), temp);
    const po::variables_map vm = temp;    
    string task = vm["tasks"].as<string>();
    string agent = vm["agents"].as<string>();
    string map = vm["map"].as<string>();
    string output;
    if (vm.count("output")){
        output = vm["output"].as<string>();
    }
    else
        output = "";
    int capacity = vm["capacity"].as<int>();

    
    bool multi_label = false;
    bool real_cost = false;  
    bool regret = false;  //true per RMCA false per MCA
    bool regret_task = false;
    srand(0);


    //Setto le opzioni 
    options options1;
    options1.multi_label = multi_label;
    options1.window_size = 0;
    options1.RM4way = 1;
    options1.f_w = 1;
    options1.ignore_target = true;
    
    constraint_strategy s = constraint_strategy::PP;
    options1.s = s;



    //Caricamento dati Kiva 
    MapLoaderCost* mapLoader;
    AgentLoader* agentLoader;
    TaskLoader* taskLoader;

    mapLoader = new MapLoaderCost();
    agentLoader = new AgentLoader();
    taskLoader = new TaskLoader();

    
    mapLoader->loadKiva(map);
    agentLoader->loadKiva(agent,capacity,*mapLoader);
    taskLoader->loadKiva(task,*mapLoader);
    

    cout<<"- Mappa caricata"<<endl;
    
    map_cols = mapLoader->cols;

    cout<<"- Task e agenti caricati"<<endl<<endl;

    cout<<"AGENTI:"<<endl;
    agentLoader->print();

    cout<<endl<<"TASKS:"<<endl;
    taskLoader->printTasks();
    cout<<endl<<endl;
    //Imposto l'obiettivo
    TA_Options ta_options;
    ta_options.objective = OBJECTIVE::TOTAL_TRAVEL_DELAY;  
    ta_options.max_iteration =10000;
    ta_options.only_top = true;  //Aggiorna solo il top dello Heap

    TaskAssignment* taskAssignment;
    if (regret_task){
        cout<<"ALGORITMO USATO : PP Regret Task"<<endl<<endl;
        taskAssignment = new TaskAssignmentRegretTask(agentLoader,taskLoader,mapLoader, ta_options, options1,real_cost,0 /*time_limit*/);
    }
    else if (!regret){
        cout<<"ALGORITMO USATO : PP"<<endl<<endl;

        taskAssignment = new TaskAssignmentPP(agentLoader,taskLoader,mapLoader, ta_options, options1,real_cost,0 /*time_limit*/);
    }


    // Inserisce tutti i task nella lista di task non assegnati
    taskAssignment->initializeOneShot();

    //Assegnamento task (RMCA)
    taskAssignment->assignTasks(output);
    
}
