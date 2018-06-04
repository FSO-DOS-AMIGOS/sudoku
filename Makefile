build:
	@echo "\nBuilding Sudoku ...\n"
	@docker build -t sudoku .

run:
	@echo "\nRunning Sudoku ...\n"
	@docker run -w /sudoku/src sudoku:latest bash -c "./sudoku"

rm:
	@echo "\nRemoving Sudoku container ...\n"
	@docker rm -f sudoku

rm-network:
	@echo "\nRemoving Sudoku network ...\n"
	@docker network rm sudoku_default

rm-img:
	@echo "\nRemoving Sudoku image ...\n"
	@docker images rmi sudoku
help:
	@echo "\n\t\t\t\tSUDOKU"
	@echo "\n\tmake build - Builds the docker image that contains the app"
	@echo "\tmake run - Runs the previously created docker image and show the output"
	@echo "\tmake rm - Removes the container created by the app"
	@echo "\tmake rm-network - Removes the default network created by the app"
	@echo "\tmake help - Outputs this list\n"
