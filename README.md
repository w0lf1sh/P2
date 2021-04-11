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

	Procedemos a explicar, el primer aproximamiento que tuvimos con el detector de actividad local. Nuestro FSA usará principalmente como variable externa la potencia de la trama de la señal para cambiar entre los estados del mismo.
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

	Para implementar esta mejora, primero modificamos pav_analysis.c y su respectivo .h para incluir una nueva función compute_init_power().

	<img src="/img/init_power_func.PNG/" align ="center">

	Añadimos dos características adicionales al tipo de estrucutra VAD_DATA, “init_power” y “trama” propias a la señal. "init_power" nos servira para conservar el valor de potencia que vamos calculando a lo largo que van pasando las tramas. Y la variable "trama" nos servira de contador.

	 <img src="/img/2caract.PNG/" align ="center">

	 Cambiamos la gestión del estado inicial del autómata.

	 <img src="/img/init_power_vad.PNG/" align ="center">

	 Como vemos, mientras no se hayan procesado 10 tramas de la señal (que asumiremos son silencio), se ira sumando la potencia de las tramas (en lineal, gracias a la función compute_init_power()). el autómata no cambiara de estado y se quedara en el estado INIT durante estas 10 tramas.
	 Una vez se haya sumado la potencia de estas 10 tramas, se calcula la media de la potencia en dBs y se asigna este valor a la variable init_power. Tambien cambiamos asi el valor del primer umbral k0.

	 Ya prácticamente implementado, solo nos falta gestionar lo que se escribe en el archivo .vad que generaremos para a posteriori comparar con los archivos .lab. 
	 Cambiamos entonces la gestión de escritura en el .vad desde la función main, para que no se escriba un undef en los casos que estamos en el estado ST_INIT, si no que en el caso de las tramas iniciales, se asuma que son de silencio.

	 <img src="/img/main_vad_init_power.PNG/" align ="center">

	 Llegamos asi a un FSCORE global de 89,757%, superando en un 5% nuestro autómata anterior. Por lo que estamos muy satisfechos con este cambio.

	 ##### Mejora implementación segundo umbral: Decisión diferida

	 Ahora estamos usando un solo umbral k0, que se define como la potencia media de las primeras tramas más unos pocos decibelios de margen. 
     Vamos a añadir otro umbral que nos permitirá ser más prudentes haciendo la decisión de que es la trama en cuestión.
	 Si estamos en silencio, y de repente superamos k0, pasaremos al estado maybe voice, no decidiendo aun si es voice o no. Definimos un segundo umbral, k1 =k0 + alfa1. Para confirmar que se trata de voz, exigimos que la potencia sea mayor a k1 pasado un cierto tiempo, si no se supera, entonces el intervalo era silencioso. 
	 Haremos lo mismo en caso de que la potencia baje de k1. No confirmaremos que se trata de un silencio, porque se puede tratar por ejemplo de un sonido fricativo sordo que se suele seguir normalmente de un sonido sonoro.

	 Modificamos entonces la gestión que hace del autómata en el vad.c:

	 <img src="/img/umbrales1.PNG/" align ="center">
	
	 Esto causara que tengamos muchas tramas clasificadas como UNDEF. Tenemos entonces que modificar lo que se hace con estas tramas en el main (ya que el evaluador entre el .vad y el .lab original no sabe comparar un trama de voz o silencio con una indefinida).
	 Tratamos de implementar lo siguiente: 

	 <img src="/img/dem.PNG/" align ="center">

	 Es decir, si el estado anterior del autómata es voz, y el nivel de potencia del segmento actual es bajo, el estado sera "maybe silence" o UNDEF en nuesto caso, y no sabremos si es realmente este estado hasta que se acabe de definir el estado de algun segmento futuro. Para ello implementamos la variable "last_defined_state" en el main que nos servira para gestionar correctamente esta dicesión diferida y no dar cabida a la escritura de una trama como UNDEF en los archivos .vad:

	 <img src="/img/umbrales2.PNG/" align ="center">
	 <img src="/img/umbrales3.PNG/" align ="center">
	 
	 Y aseguramos que al acabar la señal en cuestión, no se pueda escribir un estado como UNDEF:

	 <img src="/img/umbrales4.PNG/" align ="center">

	 Si evaluamos nuestro programa en la base de datos, modificando los valores de los umbrales manualmente, llegamos a un FSCORE global de 90,378%

	 <img src="/img/90.PNG/" align ="center">
	  


- Inserte una gráfica en la que se vea con claridad la señal temporal, el etiquetado manual y la detección
  automática conseguida para el fichero grabado al efecto. 

  ##### Ajuste de picos iniciales y final para mejorar la clasificación

  Al principio del audio hay un pequeño ruido que, aunque a priori parece que no afecta mucho, al realizar el power plot vemos que puede realmente confundir al sistema de clasificación:

  <img src="/img/pico.PNG/" align ="center">

  Como se puede ver, el fragmento está marcado como silencio manualmente pero la potencia no es baja, por eso se recortará el fragmento.
  Se procede a recortar y a mover las labels a donde tocan:

  <img src="/img/no_pico.PNG/" align ="center">
  
  Nuevas labels:

  <img src="/img/new_labeles.PNG/" align ="center">

  ##### Evaluación sobre nuestro fichero .wav
  
  Generamos el .vad con el programa vad. Y evaluamos gracias al script vad_evaluation el rendimiento de nuestro detector sobre la señal, este es el resultado: 

  <img src="/img/eval_wav.PNG/" align ="center">

  Viusalizamos con wavesurfer para ver el resultado de manera gráfica.

  <img src="/img/wavesurfer2.PNG/" align ="center">

- Explique, si existen. las discrepancias entre el etiquetado manual y la detección automática.

 Vemos que a menudo hay pequeñas tramas de silencio. Estas parecen aparecer cuando nos aproximamos o salimos de tramos de voz. Esto ocurre cuando el autómata duda y no sabe clasificar la trama y se queda en indefinido. Todas estas pequeñas tramas que vemos en la imagen son silencio, por lo que parece que la puntuación de 94% de antes parece razonable.

 Si que hay pequeñas discrepancias. Nuestro autómata no es óptimo del todo y se podría mejorar haciendo que la decisión diferida se haga por tiempo de tramas, teniendo en cuentra otras característias de la señal a parte e la potencia que nos sirvan para discernir si una trama es silencio o voz (por ejemplo la tasa de ruces por 0 o la amplitud). Tmabien se podría hacer un análisis frecuencial de las tramas y mirar tanto la DFT como la densidad de potencia para mejorar el rendimiento de nuestro detector.

### Trabajos de ampliación

#### Cancelación del ruido en los segmentos de silencio

- Si ha desarrollado el algoritmo para la cancelación de los segmentos de silencio, inserte una gráfica en
  la que se vea con claridad la señal antes y después de la cancelación (puede que `wavesurfer` no sea la
  mejor opción para esto, ya que no es capaz de visualizar varias señales al mismo tiempo).

  Antes de sustituir las tramas de silencio por 0, nos hace falta tener disponibles unas tramas que sustituir.
  Gracias a la función sf_write_float(), vamos escribiendo trama a trama en el fichero .wav de salida (en caso de haberlo especificado al invocar el programa vad)

  <img src="/img/0_1.PNG/" align ="center">

  Tras haber escrito en el .vad el tipo de trama estimada por el automata, en caso de que sea silencio, tendremos que volver hacia atrás exactamente frame_size (ya que la acabamos de escribir), para posteriormente sobreescribir los valores de esta trama, por 0’s (gracias al buffer_zeros ya dado). Usamos la función sf_seek() para movernos al principio de la trama que acabamos de escribir.

  <img src="/img/sf_seek.PNG/" align ="center">

  Como vemos el caso de error se da cuando esta función devuelve un -1, por lo que verificamos este caso en un if:

  <img src="/img/0_2.PNG/" align ="center">

  Probamos el funcionamiento: 

  <img src="/img/0_3.PNG/" align ="center">

  Percibimos absolutamente toda la voz, con las tramas de ruido en silencio total. Para poder verlo gráficamente procedemos a realizar un simple código en python para poder compararlo.

  Código en python: 

  <img src="/img/python.PNG/" align ="center">

  Gráfica: 

  <img src="/img/graph.PNG/" align ="center">

  Se ve claramente en los segmentos más estrechos (ruido) como se estrechan aun más tras haber sido reemplazados por 0’s.
  
#### Gestión de las opciones del programa usando `docopt_c`

- Si ha usado `docopt_c` para realizar la gestión de las opciones y argumentos del programa `vad`, inserte
  una captura de pantalla en la que se vea el mensaje de ayuda del programa.

  Busquemos una manera más inteligente de decidir la diferencia de dbs entre silencio y voz (umbral decisión).
  Usaremos el docopt (language for description of command-line interfaces). Lo usaremos para pasar el valor de diferencia.
  Modifiquemos primero el fichero vad.docopt. La diferencia que estableceremos por consola tendra como nombre "alfa0".

  <img src="/img/doc1.PNG/" align ="center">

  Ahora cuando compilemos (con la ayuda del programa docopt_c.py), se incorporarán estos cambios en vad_docopt.h

  <img src="/img/doc2.PNG/" align ="center">
  <img src="/img/doc3.PNG/" align ="center">

  Añadimos entonces el nuevo parámetro en la estructura de datos VAD_DATA definida en vad.h:

  <img src="/img/doc4.PNG/" align ="center">

  Seguidamente asignamos el valor de alfa0 en el vad.c y en el fichero main instanciamos el argumeno alfa0, recordando que este se pasa como una cadena de carácteres, por lo que hace falta cambiarlo por un float.

  <img src="/img/doc5.PNG/" align ="center">
  

### Contribuciones adicionales y/o comentarios acerca de la práctica

- Indique a continuación si ha realizado algún tipo de aportación suplementaria (algoritmos de detección o 
  parámetros alternativos, etc.).

  A parte de haber realizado los trabajos de ampliación, hemos propuesto un pequeño código en python que nos permite comparar un fichero .wav original con el mismo pero habiendo puesto a 0 las tramas de voz.

  Hemos tenido un pequeño problema con el plot de python porque no nos salía nada una vez ejecutabamos el grafico.py.
  Por lo que hemos modificado el bashrc para la configuración del XLaunch con nuestro display:

	<img src="/img/bash1.PNG/" align ="center">
	<img src="/img/bash2.PNG/" align ="center">

- Si lo desea, puede realizar también algún comentario acerca de la realización de la práctica que
  considere de interés de cara a su evaluación.

  Esta práctica, a pesar de haber tenido que realizarla en poco margen de tiempo, nos ha parecido extremadamente interesante por todo el contenido que abarca. El modelo matemática FSA, su mejora y el estudio de las caracteristicas de la señal han sido algunos de los aspectos más instructivos de este laboratorio.

  Aun y habiendo llegado a un humilde 90 y pico por ciento de puntuación global en la base de datos, creemos que si hubiesemos implementado algunas otras caracteristicas para la decisión de si un estado es voz o silencio (por ejemplo el tiempo de una trama, o la taasa de cruces por cero), o hubiesemos distinguido mejor el estado undefined como dos estados "maybe voice" o "maybe silence" para realizar un código de main más claro, podríamos haber mejorado aún más la puntuación.

  Nos quedamos con lo aprendido, y esperamos poder mejorar nuestras marcas de aquí en adelante.

  P.D: Las respuestas a los ejercicios de aquí, se han ido cogiendo de una "memoria" previa que estabamos realizando a medida que completabamos la práctica. Es posible que en esta [Memoria](https://docs.google.com/document/d/102KvfJR59AU95sfetlRobyF2WO-y05IFTsNGPvg07x8/edit?usp=sharing) haya alguna captura o comentario suplementario que no tenian cabida a las respuestas de este. La evaluación sabemos que se hace con el README.md, pero queríamos dejar un enlace por aqui a la otra memoria por si acaso.

### Antes de entregar la práctica

Recuerde comprobar que el repositorio cuenta con los códigos correctos y en condiciones de ser 
correctamente compilados con la orden `meson bin; ninja -C bin`. El programa generado (`bin/vad`) será
el usado, sin más opciones, para realizar la evaluación *ciega* del sistema.

