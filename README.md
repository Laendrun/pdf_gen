# PDF Gen

This is a simple C program that uses some simple libraries to generate some pdf files for me.

The files that can be generated are :

- Business offers
- Order confirmation
- Invoices

## Compiling

To compile the program simply run the following command in the root directory :

```shell
make
```

This will compile all the necessary files into an executable called *pdf_gen*.

## Run the program

### Prerequisites

First off, you have to create 2 CSV files :

- customers.csv
- sales_lines.csv

Example files are available in the repository, these files contain the structure needed for the program to function properly.

These files have to be in the root directory for now, or at least in the same directory as the binary.

These files are the mandatory files.
I also use some images for my logo and the Twint QR Code but for now, I don't have the ability to change the path to the images or the name of the images so this will be in the improvements. (Not required, you won't be able to generate complete invoices though).

### Generate the documents

To generate the different documents, run the following commands :

#### Business offers

```shell
./pdf_gen 0 CLT00001 2200001
```

#### Order confirmation

```shell
./pdf_gen 1 CLT00001 2200001
```

#### Invoices

```shell
./pdf_gen 2 CLT00001 2200001
```

## Improvements

- [ ] Specifiy the path to a config file
  - [ ] oc_output_path
  - [ ] cv_output_path
  - [ ] fa_output_path
  - [ ] sales_lines_input_path
  - [ ] customers_files_path
  - [ ] logo_file_path
  - [ ] twint_directives_path
  - [ ] twint_qr_code_path