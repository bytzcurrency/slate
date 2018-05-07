#!/bin/bash

find . -iname "*pivx*" -exec rename 's/slate/slate/' '{}' \;
find . -iname "*zpiv*" -exec rename 's/zpiv/zslx/' '{}' \;

find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/PIVX/SLATE/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/PivX/Slate/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/pivx/slate/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/Pivx/Slate/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/zPIV/zSLX/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/zPiv/zSlx/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/zpiv/zslx/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/ZPIV/ZSLX/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/ZPiv/ZSlx/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/Zpiv/Zslx/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/PIV/SLX/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/Piv/Slx/g'
find . -path ./.git -prune -o -type f -name '*' -print0| xargs -0 sed -i 's/piv/slx/g'

# TODO: exclude pivx (core) developers
# TODO: add copyright notices for slate
