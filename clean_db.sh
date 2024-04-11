#!/bin/bash

folder_database="./database"

find "${folder_database}" -type f -print0 | xargs -0 rm -f
