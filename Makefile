PRG            = NXTsw
FW		= 128


# Override is only needed by avr-lib build system.

all: clean
	#cp $(PRG).c $(PRG).nxc
	nbc -EF -v=$(FW) $(PRG).nxc -O=$(PRG).rxe
	@mv $(PRG).rxe `echo -n $${PWD##*/}|tr " " "-" && echo ".rxe"`
clean:
	@rm -rf *.rxe

install: all play

load:
	@nbc -EF -d -b `echo -n $${PWD##*/}|tr " " "-" && echo ".rxe"`

play:
	@nbc -EF -r -b `echo -n $${PWD##*/}|tr " " "-" && echo ".rxe"`
