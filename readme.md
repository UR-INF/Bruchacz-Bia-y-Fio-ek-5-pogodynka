# Pogodynka - dokumentacja projektowa
##  Temat projektu i nazwa aplikacji
Pogodynka - to aplikacja desktopowa, która pozwala użytkownikowi monitorować pogodę oraz czas dla wybranych przez niego lokalizacji. Elementem wyróżniającym aplikację na tle konkurencji jest tytułowa wirtualna pogodynka, która w zależności od warunków atmosferycznych zmienia swój ubior. Dzięki temu użytkownik nie będzie miał problemu z ubiorem adekwatnym do pogody.

## Cel i opis projektu
Funkcjonalności aplikacji:
* Jako użytkownik chcę mieć możliwość sprawdzenia pogody na najbliższy czas.
* Jako użytkownik chce mieć możliwość sprawdzenia temperatury, ciśnienia, wilgotności, wschódu słońca, zachódu słońca, strefy czasowej, zachmurzenia, prędkości wiatru.
* Jako użytkownik chcę mieć możliwość wyboru kraju oraz miasta, abym mógł sprawdzić pogodę dla określonej lokalizacji.
* Jako użytkownik chcę mieć możliwość wyświetlenia w formie obrazków proponowanego ubioru dla danych warunków atmosferycznych.
* Jako użytkownik chcę mieć możliwość wyświetlenia wykresów dla wybranych parametrów pogodowych.
* Jako użytkownik chcę mieć możliwość wyświetlania godziny dla wybranej lokalizacji.

## Technologie
* API Win32
  * Aplikacja okienkowa w języku C++
* Weather API

## Instalacja

- [VCPKG](https://github.com/microsoft/vcpkg) -menedżer pakietów dla C++ 
```sh
$ > git clone https://github.com/Microsoft/vcpkg.git
$ > cd vcpkg

$ PS> .\bootstrap-vcpkg.bat
$ Linux:~/$ ./bootstrap-vcpkg.sh
```
-Następnie(potrzebne uruchomienie jako administrator)
```sh
$ PS> .\vcpkg integrate install
$ Linux:~/$ ./vcpkg integrate install
```
- Instalacja pakietów
```sh
$ PS> .\vcpkg install curl:x64-windows
$ PS> .\vcpkg install jsoncpp
$ PS> .\vcpkg install rapidjson
```
## Wykonał:
- Paweł Fiołek
- Alan Biały
- Patryk Brzuchacz

## Przykładowe użycie aplikacji:

<br />
<p align="center">
  <img height="450" src="ss/1.png"> 
</p>
<br/>
<br />
<p align="center">
  <img height="450" src="ss/2.png"> 
</p>
<br/>
<br />
<p align="center">
  <img height="450" src="ss/3.png"> 
</p>
<br/>
<br />
<p align="center">
  <img height="450" src="ss/4.png"> 
</p>
<br/>
<br />
<p align="center">
  <img height="450" src="ss/5.png"> 
</p>
<br/>
<br />
<p align="center">
  <img height="450" src="ss/6.png"> 
</p>
<br/>
