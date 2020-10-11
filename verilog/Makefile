all:
	rm -rf work
	vlib work
	vlog *v
	vsim -c -do "run -all" powtb

clean:
	rm -rf work transcript
