PRG            = NXTsw
FW		= 126


# Override is only needed by avr-lib build system.

all: clean
	cp $(PRG).c $(PRG).nxc
	nbc -v=$(FW) $(PRG).nxc -O=$(PRG).rxe
	@mv $(PRG).rxe `echo -n $${PWD##*/}|tr " " "-" && echo ".rxe"`
clean:
	@rm -rf *.rxe

install: all play

load:
	@nbc -d -b `echo -n $${PWD##*/}|tr " " "-" && echo ".rxe"`

play:
	@nbc -r -b `echo -n $${PWD##*/}|tr " " "-" && echo ".rxe"`
