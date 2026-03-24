This project is in ***very*** early development and will likely not be ready for a **long** time.
I plan on working on it casually when I feel like it, so no promises about anything really.  

Tori is (will be?) a programming language focused on usability, easiness to type, and unique design while still being fun to use.
I made this language because I thought it would be a cool project (it is).
Also because there is no language that mixes the elements that I want (simple, readable, but without the shortcomings of dynamic typing and indentation-based separation).  

***So, why use Tori?***  
Don't.  

No, I'm being serious.  

Don't get me wrong, it would be very cool to have Tori become a large, widely used langauge. But I still designed and developed it with me specifically in mind.
It's not going to work for everyone, and that's fine with me.
On top of that, despite being in its like 5th iteration (idk I lost count), this is still my first language.
I don't expect it to be *perfect* on the first try (or 7th) but for many people, there will likely be *features* (problems) with the language that kill the language for them.
I'm aware that making something deliberately unusual or different may lead to poor choices that sacrifice good design philosophy, but it is specifically this uniqueness that lead me to get the idea to make a programming language in the first place, so I am going to stick with it.  
Maybe it'll even become good enough for actual use (beyond myself) eventually.  

Example planned syntax is stored in [example-syntax.md](example-syntax.md).  

Documentation on the purpose of specfic files can be found in [structure.md](structure.md).  

## Build requirements:
- `make`
- `gcc`  

To build, navigate to the location where you cloned this repository, and run `make`.

### Extra Windows steps:
Windows users should first install `msys2`, then open the msys2 shell.
In the shell, run the following command:
```bash
pacman -S make gcc
```
This installs `make` and `gcc` on your system. Running `make` from an `msys2` or Git Bash shell while in the directory where you cloned the repository should build Tori.  