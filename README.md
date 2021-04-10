PAV - P2: detección de actividad vocal (VAD)
============================================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 2](https://github.com/albino-pav/P2),
y una parte de su gestión se realizará mediante esta web de trabajo colaborativo.  Al contrario que Git,
GitHub se gestiona completamente desde un entorno gráfico bastante intuitivo. Además, está razonablemente
documentado, tanto internamente, mediante sus [Guías de GitHub](https://guides.github.com/), como
externamente, mediante infinidad de tutoriales, guías y vídeos disponibles gratuitamente en el abismo del oscuro y perturbante internet.


Inicialización del repositorio de la práctica.
----------------------------------------------

Para cargar los ficheros en su ordenador personal debe seguir los pasos siguientes:

*	Abra una cuenta GitHub para gestionar esta y el resto de prácticas del curso.
*	Cree un repositorio GitHub con el contenido inicial de la práctica (sólo debe hacerlo uno de los
	integrantes del grupo de laboratorio, cuya página GitHub actuará de repositorio central del grupo):
	-	Acceda la página de la [Práctica 2](https://github.com/albino-pav/P2).
	-	En la parte superior derecha encontrará el botón **`Fork`**. Apriételo y, después de unos segundos,
		se creará en su cuenta GitHub un proyecto con el mismo nombre (**P2**). Si ya tuviera uno con ese 
		nombre, se utilizará el nombre **P2-1**, y así sucesivamente.
*	Habilite al resto de miembros del grupo como *colaboradores* del proyecto; de este modo, podrán
	subir sus modificaciones al repositorio central:
	-	En la página principal del repositorio, en la pestaña **:gear:`Settings`**, escoja la opción 
		**Collaborators** y añada a su compañero de prácticas.
	-	Éste recibirá un email solicitándole confirmación. Una vez confirmado, tanto él como el
		propietario podrán gestionar el repositorio, por ejemplo: crear ramas en él o subir las
		modificaciones de su directorio local de trabajo al repositorio GitHub.
*	En la página principal del repositorio, localice el botón **Branch: master** y úselo para crear
	una rama nueva con los primeros apellidos de los integrantes del equipo de prácticas separados por
	guion (**fulano-mengano**).
*	Todos los miembros del grupo deben realizar su copia local en su ordenador personal.
	-	Copie la dirección de su copia del repositorio apretando en el botón **Clone or download**.
		Asegúrese de usar *Clone with HTTPS*.
	-	Abra una sesión de Bash en su ordenador personal y vaya al directorio **PAV**. Desde ahí, ejecute:

		```.sh
		git clone dirección-del-fork-de-la-práctica
		```

	-	Vaya al directorio de la práctica `cd P2`.
	-	Añada la etiqueta `origin` a su copia del repositorio. Esto es útil para facilitar los *push* y
		*pull* al repositorio original:
		```.sh
		git remote add origin dirección-del-fork-de-la-práctica
		```
	-	Cambie a la rama **fulano-mengano** con la orden:

		```.sh
		git checkout fulano-mengano
		```

*	A partir de este momento, todos los miembros del grupo de prácticas pueden trabajar en su directorio
	local del modo habitual.
	-	También puede utilizar el repositorio remoto como repositorio central para el trabajo colaborativo
		de los distintos miembros del grupo de prácticas; o puede serle útil usarlo como copia de
		seguridad.
	-	Cada vez que quiera subir sus cambios locales al repositorio GitHub deberá confirmar los
		cambios en su directorio local:

		```.sh
		git add .
		git commit -m "Mensaje del commit"
		```

		y, a continuación, subirlos con la orden:

		```.sh
		git push -u origin fulano-mengano
		```

*	Al final de la práctica, la rama **fulano-mengano** del repositorio GitHub servirá para remitir la
	práctica para su evaluación utilizando el mecanismo *pull request*.
	-	Vaya a la página principal de la copia del repositorio y asegúrese de estar en la rama
		**fulano-mengano**.
	-	Pulse en el botón **New pull request**, y siga las instrucciones de GitHub.


Entrega de la práctica.
-----------------------

Responda, en este mismo documento (README.md), los ejercicios indicados a continuación. Este documento es
un fichero de texto escrito con un formato denominado _**markdown**_. La principal característica de este
formato es que, manteniendo la legibilidad cuando se visualiza con herramientas en modo texto (`more`,
`less`, editores varios, ...), permite amplias posibilidades de visualización con formato en una amplia
gama de aplicaciones; muy notablemente, **GitHub**, **Doxygen** y **Facebook** (ciertamente, :eyes:).

En GitHub. cuando existe un fichero denominado README.md en el directorio raíz de un repositorio, se
interpreta y muestra al entrar en el repositorio.

Debe redactar las respuestas a los ejercicios usando Markdown. Puede encontrar información acerca de su
sintáxis en la página web [Sintaxis de Markdown](https://daringfireball.net/projects/markdown/syntax).
También puede consultar el documento adjunto [MARKDOWN.md](MARKDOWN.md), en el que se enumeran los
elementos más relevantes para completar la redacción de esta práctica.

Recuerde realizar el *pull request* una vez completada la práctica.

Ejercicios
----------

### Etiquetado manual de los segmentos de voz y silencio

- Etiquete manualmente los segmentos de voz y silencio del fichero grabado al efecto. Inserte, a 
  continuación, una captura de `wavesurfer` en la que se vea con claridad la señal temporal, el contorno de
  potencia y la tasa de cruces por cero, junto con el etiquetado manual de los segmentos.

<img src="/img/wavesurfer1.PNG/" align ="center">


- A la vista de la gráfica, indique qué valores considera adecuados para las magnitudes siguientes:

	* Incremento del nivel potencia en dB, respecto al nivel correspondiente al silencio inicial, para
	  estar seguros de que un segmento de señal se corresponde con voz.

	  Silencio principal: Alrededor de los 14 dBs, pico de ruido de silencio inicial en 51 dBs, pasando antes por un incremento hasta 36dbs (salto de 15 dBs), luego primera palabra pasa de 16.15 dBs a lo que parece ser una fricativa sorda que lleva la señal a una potencia de 48,89dBs, para seguidamente subir a una potencia de 62,7 dBs para la primera palabra (comenzada en consonante y vocal : “PA”). 
	  Parece que un valor mínimo del incremento podría ser de unos 14dBs, determinando así la transición de un segmento de silencio a uno de voz. Parece que se cumple con el resto de segmentos.

	* Duración mínima razonable de los segmentos de voz y silencio.

	  Duración mínima segmento voz: 0,55s
	  Duración mínima segmento silencio: 0,41s

### Desarrollo del detector de actividad vocal

- Complete el código de los ficheros de la práctica para implementar un detector de actividad vocal tan
  exacto como sea posible. Tome como objetivo la maximización de la puntuación-F `TOTAL`.

	#### Puesta en marcha de una primera versión del detector

	Procedemos a explicar, el primer aproximamiento qu tuvimos con el detector de actividad local. Nuestro FSA usará principalmente como variable externa la potencia de la trama de la señal para cambiar entre los estados del mismo.
	Entonces primero tendremos que añadir a nuestro proyecto pav_analysis.c, desarollado en la práctica 1 para la extracción de las caracteristicas de las tramas como pueden ser: la potencia, la tasa de cruces por cero o la amplitud media. 

	<img src="/img/anadir_pavanalysis.PNG/" align ="center">

	Modificamos el fichero de dependencia meson.build para que las compilaciones y los enlazados tengan en cuenta el nuevo .c añadido.

	<img src="/img/meson.PNG/" align ="center">

	Procedemos entonces a completar la función compute_features() de vad.c. La implementación de esta función sera sencilla ya que usaremos directamente las funciones que desarollamos en pav_analysis.c

	<img src="/img/compute_features.PNG/" align ="center">

	Pasamos entonces ha realizar una primera proposición de nuestra máquina de estados. Como hemos dicho anteriormente, nuestro autómata se basara principalmente en la potencia de la trama. Por lo que en la función vad(), encargada en el main de informar sobre el estado de la trama actual, inicializamos un primer umbral k0 que distinga las tramas de voz de las de silencio. En esta primer aproximación el valor del umbral sera: la potencia de la primera trama (que asumimos siempre sera silencio) + 30dBs. Si la potencia de la trama actual supera este valor, entonces asumimos que la trama actual es de voz, y si no, de silencio.

	<img src="/img/1erVad.PNG/" align ="center">

	La detección resulta ser pésima entre otras cosas por el valor de diferencia de 30 dB's. Cambiamos este valor de diferencia por un parámetro que precisaremos por consola. La implementación de este apartado en particular se vera más en detalle en el apartado de trabajos de ampliación: "Gestión de las opciones del programa usando `docopt_c`"

	Al cambiar entonces esta diferencia por una por defecto de 10dB's, llegamos a la detección de tramas de voz/silencio óptima por ahora. Evaluamos los resultados sobre la base de datos `db.v4` con el script `vad_evaluation.pl` para poder ver la tasa de sensibilidad (indica el tanto por ciento de veces que las realizaciones de la clase se detectan como tales) y precisión (indica tanto por ciento de veces que las realizaciones detectadas como pertenecientes a la clase realmente lo son) de nuestra máquina de estados. Estos nos serviran para calcular la medida-F que toma en cuenta estos parámetros de evaluación (la evaluación final realmente se hara con medidas-F ponderadas).
	Enfin, por el momento, siendo el 100% un detector perfecto, tenemos un detector que cumple un 84,761%.

	<img src="/img/1erRes.PNG/" align ="center">

	#### Mejora del autómata
	##### Mejora estimación del primer umbral: Potencia media inicial

	k0, nuestro primer umbral, toma actualmente toma el valor medido de potencia en la primera trama del audio + una diferencia. Esta base sobre la que se construye el umbral, parece muy mejorable. Por lo que como primera mejora, en lugar de tomar el valor medido de potencia en la primera trama, tomaremos el valor de potencia medias de las N primeras tramas:

	<img src="/img/pot.PNG/" align ="center">

	



- Inserte una gráfica en la que se vea con claridad la señal temporal, el etiquetado manual y la detección
  automática conseguida para el fichero grabado al efecto. 


- Explique, si existen. las discrepancias entre el etiquetado manual y la detección automática.



### Trabajos de ampliación

#### Cancelación del ruido en los segmentos de silencio

- Si ha desarrollado el algoritmo para la cancelación de los segmentos de silencio, inserte una gráfica en
  la que se vea con claridad la señal antes y después de la cancelación (puede que `wavesurfer` no sea la
  mejor opción para esto, ya que no es capaz de visualizar varias señales al mismo tiempo).

#### Gestión de las opciones del programa usando `docopt_c`

- Si ha usado `docopt_c` para realizar la gestión de las opciones y argumentos del programa `vad`, inserte
  una captura de pantalla en la que se vea el mensaje de ayuda del programa.


### Contribuciones adicionales y/o comentarios acerca de la práctica

- Indique a continuación si ha realizado algún tipo de aportación suplementaria (algoritmos de detección o 
  parámetros alternativos, etc.).

- Si lo desea, puede realizar también algún comentario acerca de la realización de la práctica que
  considere de interés de cara a su evaluación.


### Antes de entregar la práctica

Recuerde comprobar que el repositorio cuenta con los códigos correctos y en condiciones de ser 
correctamente compilados con la orden `meson bin; ninja -C bin`. El programa generado (`bin/vad`) será
el usado, sin más opciones, para realizar la evaluación *ciega* del sistema.

Memoria: Detección de actividad vocal (VAD)
----------------------------------------------
En la segunda práctica del laboratorio de PAV, vamos a realizar un detector de voz a través de la extracción de características (sobre todo la potencia) de la señal. Los criterios que usemos para decidir cuando un segmento de señal es voz o silencio, lo implementaremos a través de un FSA o autómata de estados finitos que decidira su estado actual y futuro en función de una variable externa (en nuestro caso, la potencia de la trama).

Como hicimos en la primera memoria, expondremos primero las tareas, seguidamente los ejercicios principales, para luego acabar con los ejercicios de ampliación y los problemas encontrados para que de esta manera podamos recurrir a esta memoria en caso de recuperar información más adelante.

### Tareas 
