# what does this do  

this program take the famous "color sort game" puzzle.  
use backtracking algorithm to solve it.  
  
## how to install  

1.load the `.exe` file.  
2.run the `.exe` file.  

## how to do the input  

1.put in the `bottle count` and `bottle size`.  

```
enterBottleCount and bottleSize
4 4
```
2.put int the value of the bottle.  
  given one number -> one specific color
  note that -1 mean terminate that bottle input for example if bottle the size of four have
  `red red blue` it will be `1 1 2 -1`
  `red` it will be `1 -1`
  `[empty]` it will be `-1`
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
