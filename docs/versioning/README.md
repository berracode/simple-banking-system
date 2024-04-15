# Sistema de versionado

Se usa un versionado semantico que incluye sufijos como: -alpha, -beta y -rc. También se incluye el uso de Major, minor y patch (x.y.z o major.minor.patch o, ejemplo: 0.1.8).

## Números de versiones

### Major
Lo incrementaremos cuando realicemos cambios en la estructura del proyecto y/o en la funcionalidad del software, que requiera que haya un proceso de adaptación.

### Minor
Cada que agreguemos nuevas características o funcionalidades, al renovar características (no corregir errores). 

### Patch
Lo incrementaremos tras corregir errores o realizar pequeños cambios, por ejemplo: agregar tilde a una letra, cambiar el color de un botón. 


## Sufijos
### Sufijo -alpha
Para versiones que están aún en desarrollo.

### Sufijo -beta
Para versiones que están en desarrollo pero en una etapa de pruebas avanzadas proximas a ser rc.

### Sufijo -rc
Refleja un estado de la aplicación cercano a ser lanzada oficialmente. Estamos realizando pruebas finales.

## Ejemplo de nuestro versionado semantico

- 0.1.0-alpha: Esta es nuestra primera versión alfa, lo cual es apropiado para indicar que estamos en una fase temprana de desarrollo y que todavía esatmos probando características principales.

- 0.1.1-alpha: Un buen paso al incrementar el número de corrección para indicar que se han abordado errores en esta versión alfa.

- 0.2.0-alpha: Aumentar el número menor para indicar que hemos agregado nuevas características en el contexto de esta versión alfa.

- 0.2.1-alpha: Actualizar el número de corrección para indicar correcciones de errores en esta fase alfa.

- 0.2.2-alpha: Otro aumento en el número de corrección para reflejar cambios menores en esta versión alfa.

- 0.3.0-beta: Aquí, cambiar a la fase beta es una buena señal de que estamos avanzando hacia la estabilidad y las pruebas más avanzadas.

- 0.3.1-beta: Corregir errores en la versión beta es una práctica común, y aumentar el número de corrección es apropiado.

- 0.4.0-rc: Cambiar a "release candidate" indica que estamos cerca de la versión final y que estamos buscando estabilidad y retroalimentación antes de la publicación.

- 0.4.1-rc: Corregir errores en la versión candidata es una práctica sensata, y aumentar el número de corrección es correcto.

- 0.4.2-rc: Lo mismo aquí, reflejar cambios menores en la versión candidata.

- 0.4.3: Finalmente, publicar la versión final con un número de corrección más alto después de las pruebas y correcciones en la versión candidata.

## GitFlow

***En construcción***


