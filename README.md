# Simple banking system written in C
## _for fun and learn about networks, unix, files and data structures_

## Future characteristics

Simple banking system will be able to execute the following operations (all operations at the file level) through CLI:

- Create account (including customer creation if it does not exist)
- deposit money to another account
- Delete the money from the accounts
- Transfer money to another account

Previous operations include the generation of the transaction record.

## Hexagonal Architecture

This is the approximate architecture that I am using for the project. I wanted it to be a project with a couple of details.


![hexagonal](./docs/img/hexagonal-architecture.jpg)


## Usage

Right now the usage is simple, the code was developed on Linux, so I'm unsure if it will run on Windows. Feel free to give it a try.

Clone project

```sh
git clone https://github.com/berracode/simple-banking-system.git
```

Go to source code's directory:


```sh
cd simple-banking-system
```

Ensure that you have  `gcc ` o  `g++ ` and  `make ` and then execute:

```sh
make
```

and finally

```sh
./bin/sysbansi
```


## License

MIT

**Free Software, Hell Yeah!**