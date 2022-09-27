# Cellular Automaton Assignment -- Thomas Pree

C++ Demonstration of Conway's Game of Life, running in a web browser. Update rules courtesy of Complexity by Melanie Mitchell. [1]

## Installation

Run compile script, and navigate to URL for web browser experience. (Ensure submodules are updated, and emsdk is installed, activated, and sourced.)
```bash
./compile-run.sh
```
Note on windows machines the URL will output wrong, so navigate to [localhost:8000](http://localhost:8000/)

## Usage

Gliders will appear by default. To view different patterns in the demonstration, modify line 149. Options include ```basic_gliders```[2], ```spaceship```[3], or ```osc```[4] (oscillators).
```
                cells[j][i] = osc[i].at(j) == 'X'; //creates various oscillators
```
## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)

## References
[[1] Mitchell. (n.d.). Complexity. Oxford University Press, Incorporated.](https://bridge.primo.exlibrisgroup.com/permalink/01BRC_INST/1tn7c8c/alma991018027657402971
)

[[2] LifeWiki Glider](https://conwaylife.com/wiki/Glider)

[[3] LifeWiki Spaceship](https://conwaylife.com/wiki/Spaceship)

[[4] LifeWiki Oscillators:](https://conwaylife.com/wiki/Oscillator)

[Blinker](https://conwaylife.com/wiki/Blinker)

[Dinner Table](https://conwaylife.com/wiki/Dinner_table)

[Figure Eight](https://conwaylife.com/wiki/Figure_eight)

[Worker Bee](https://conwaylife.com/wiki/Worker_bee)