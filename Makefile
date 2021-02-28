RED	=						\033[0;31m
BOLD_RED =			\033[1;31m
GREEN =					\033[0;32m
BOLD_GREEN =		\033[1;32m
YELLOW =				\033[0;33m
BOLD_YELLOW =		\033[1;33m
BLUE =					\033[0;34m
BOLD_BLUE=			\033[1;34m
MAGENTA =				\033[0;35m
BOLD_MAGENTA =	\033[1;35m
CYAN =					\033[0;36m
BOLD_CYAN =			\033[1;36m
NC =						\033[0m
BOLD_NC =       \033[1;39m
NL = 						\n

CC = @gcc
CFLAGS = -std=gnu90

targets: main analyzer report

main: src/main.c src/util.c
	$(CC) $(CFLAGS) -o bin/main src/main.c src/util.c

analyzer: src/analyzer.c src/util.c
	$(CC) $(CFLAGS) -o bin/analyzer src/analyzer.c src/util.c

report: src/report.c src/util.c
	$(CC) $(CFLAGS) -o bin/report src/report.c src/util.c

clean:
	@rm -f -r bin
	@echo "$(CYAN)┌─────────────────────────────────────────────┐"
	@echo "│ $(BOLD_NC)clean$(NC) completato                            $(CYAN)│"
	@echo "└─────────────────────────────────────────────┘$(NC)"

build:
	@if [ -d bin ]; then\
		make -s clean;\
	fi
	@mkdir bin
	@make -s targets
	@echo "$(CYAN)┌─────────────────────────────────────────────┐"
	@echo "│ $(BOLD_NC)build$(NC) completato                            $(CYAN)│"
	@echo "└─────────────────────────────────────────────┘"
	@echo "╔═════════════════════════════════════════════╗"
	@echo "║ $(BOLD_CYAN)BENVENUTO$(CYAN)                                   ║"
	@echo "╠═════════════════════════════════════════════╣"
	@echo "║ $(BOLD_NC)  Modalità 'Main'                           $(CYAN)║"
	@echo "║                                             ║"
	@echo "║ $(NC)Digita $(BOLD_NC)bin/main$(NC) per eseguire il progetto in$(CYAN) ║"
	@echo "║ $(NC)un terminale con una shell interattiva.$(CYAN)     ║"
	@echo "╠═════════════════════════════════════════════╣"
	@echo "║ $(BOLD_NC)  Modalità 'Analyzer e Report'              $(CYAN)║"
	@echo "║                                             ║"
	@echo "║ $(NC)Digita $(BOLD_NC)bin/analyzer n m path/to/file$(CYAN)        ║"
	@echo "║ $(NC)e $(BOLD_NC)bin/report$(NC) in due terminali.$(CYAN)              ║"
	@echo "╠═════════════════════════════════════════════╣"
	@echo "║ $(NC)Digita $(BOLD_NC)make help$(NC) per informazioni più$(CYAN)       ║"
	@echo "║ $(NC)dettagliate.$(CYAN)                                ║"
	@echo "╚═════════════════════════════════════════════╝"
	@echo "\n$(NC)"

help:
	@echo "$(CYAN)"
	@echo "┌─────────────────────────────────────────────┐"
	@echo "│ $(BOLD_CYAN)HELP$(CYAN)                                        │"
	@echo "└─────────────────────────────────────────────┘"
	@if [ ! -d bin ]; then\
		echo "┌─────────────────────────────────────────────┐";\
		echo "│ $(NC)Digita $(BOLD_NC)make build$(NC) per compilare i file      $(CYAN)│";\
		echo "│ $(NC)sorgenti.                                   $(CYAN)│";\
		echo "├─────────────────────────────────────────────┤";\
	else\
	 echo "┌─────────────────────────────────────────────┐";\
	fi
	@echo "│ $(BOLD_NC)  Modalità 'Main'                           $(CYAN)│"
	@echo "│                                             │"
	@echo "│ $(NC)Digita $(BOLD_NC)bin/main$(NC) per eseguire il progetto in $(CYAN)│"
	@echo "│ $(NC)un terminale con una shell interattiva.     $(CYAN)│"
	@echo "├─────────────────────────────────────────────┤"
	@echo "│ $(BOLD_NC)  Modalità 'Analyzer e Report'              $(CYAN)│"
	@echo "│                                             │"
	@echo "│ $(NC)Digita $(BOLD_NC)bin/analyzer n m path/to/file$(NC) e      $(CYAN)│"
	@echo "│ $(BOLD_NC)bin/report$(NC) in due terminali.                $(CYAN)│"
	@echo "│                                             │"
	@echo "│ $(NC)n, m > 0                                    $(CYAN)│"
	@echo "│                                             │"
	@echo "│ $(NC)Il path al file può indicare un qualsiasi   $(CYAN)│"
	@echo "│ $(NC)file, o una qualsiasi cartella.             $(CYAN)│"
	@echo "│ $(NC)I contenuti della cartella verranno         $(CYAN)│"
	@echo "│ $(NC)analizzati.                                 $(CYAN)│"
	@echo "│ $(NC)Inserisci più path separati con uno spazio. $(CYAN)│"
	@echo "│                                             │"
	@echo "│ $(NC)Esempi di path:                             $(CYAN)│"
	@echo "│ $(NC)> filename                                  $(CYAN)│"
	@echo "│ $(NC)> filename.txt                              $(CYAN)│"
	@echo "│ $(NC)> path/to/filename.txt                      $(CYAN)│"
	@echo "│ $(NC)> \"file name with spaces.txt\"               $(CYAN)│"
	@echo "│ $(NC)> foldername                                $(CYAN)│"
	@echo "│ $(NC)> path/to/foldername                        $(CYAN)│"
	@echo "└─────────────────────────────────────────────┘"
	@echo "┌─────────────────────────────────────────────┐"
	@echo "│ $(NC)Digita $(BOLD_NC)make clean$(NC) per rimuovere i file      $(CYAN)│"
	@echo "│ $(NC)temporanei.                                 $(CYAN)│"
	@echo "└─────────────────────────────────────────────┘"

	@echo "$(NC)\n"
