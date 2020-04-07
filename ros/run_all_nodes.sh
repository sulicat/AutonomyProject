#!/bin/bash

echo "Running all nodes: "

nodes=( "simple_car_model"
	"vehicle_controller"
	"world_vis" )

kill_nodes () {
    for n in ${nodes[@]}; do
	pkill ${n}_node
    done
}

run_nodes () {
    for n in ${nodes[@]}; do
	./devel/lib/$n/${n}_node &
    done
}



options=("Run" "Kill")

select opt in ${options[@]}
do
    case $opt in
	"Run")
	    run_nodes
	    break
	    ;;
	"Kill")
	    kill_nodes
	    break
	    ;;
	*) echo "Invalid bro";;
    esac
done
