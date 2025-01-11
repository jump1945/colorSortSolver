# what does this do  

this program take the famous "color sort game" puzzle  
and use recursive backtracking algorithm to solve it.  
  
## how to install  

1.load the `.exe` file.  
2.run the `.exe` file.  

## how to do the input  

1.put in the `bottle count` and `bottle size` in the following order.  

```
enterBottleCount and bottleSize
4 4
```
2.put in the value of the bottle.  
  given one number -> one specific color  
  note that -1 mean terminate that bottle input for example if bottle the size of four have  
  `red red blue` it will be `1 1 2 -1`  
  `red`          it will be `1 -1`  
  `[empty]`      it will be `-1`  
```
bottle : 1 value
1 1 2 2
bottle : 2 value
2 2 1 1
bottle : 3 value
3 3 3 3
bottle : 4 value
-1
```

## what does the output mean  

the part under is show of how program solve the bottle problem , it is not very readable and you can ignore it.  
```
2 2 |
1 1 |
2 2 1 1 |
3 3 3 3 |
---------------------
1 1 1 1 |
2 2 |
2 2 |
3 3 3 3 |
---------------------
1 1 1 1 |
|
2 2 2 2 |
3 3 3 3 |
---------------------
```
this part is solution to the problem , it could be slightly redundant sometimes.  
if the program output `1 4` that mean to tranfer from bottle 1 to bottle 4.  
```
1 4
2 1
4 2
```
## why does the program output nothing
this is caused by the algorithm not finding solution.  
