# Tower Defense - Taller de Programación I

## [Enunciado](https://drive.google.com/file/d/0BxzMpd1uc48tWWphb1NMVVppTkU/view?usp=sharing)
## [Informe](https://docs.google.com/document/d/1e3LkHYn57xLM4v-8pcsPrcFFL5O7Mjm2l2rr5pzXS2s/edit?usp=sharing)

Para compilar:       
#### `sudo apt-get install libgtkmm-3.0-dev libyaml-cpp-dev libsdl2-dev libsdl2-mixer-dev`
#### `cmake . && make`
Es necesaria una carpeta /maps junto al ejecutable Server, los .wav de ejemplo (en src/sound_test) junto al ejecutable SoundTest, y las carpetas editor/assets y client/sprites junto a los ejecutables respectivos.     
Client y Server solo toman un argumento por línea de comandos: el puerto.
