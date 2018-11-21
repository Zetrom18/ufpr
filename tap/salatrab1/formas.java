class circulo{
	
	private static int raio;

	public static double getArea(){
		return (raio*raio*3.14);
	} 

	public static double getPerimetro(){
		return (raio*2*3.14);
	}

	public static void setRaio(int r){
		raio = r;
	}

	public static int getRaio(){
		return (raio);
	}

	public circulo(int r){
		raio = r;
	}

}

class quadrado{

	private static int lado;

	public static int getArea(){
		return (lado*lado);
	}

	public static int getPerimetro(){
		return (lado*4);
	}

	public static int getLado(){
		return lado;
	}

	public static void setLado(int l){
		lado = l;
	}

	public quadrado(int l){
		lado = l;
	}

}

class retangulo{

	private static int altura,comprimento;

	public static int getArea(){
		return (altura*comprimento);
	}

	public static int getPerimetro(){
		return (altura*2+comprimento*2);
	}

	public static void setAltura(int a){
		altura = a;
	}

	public static void setComprimento(int c){
		comprimento = c;
	}

	public static int getAltura(){
		return altura;
	}

	public static int getComprimento(){
		return comprimento;
	}

	public retangulo(int l1, int l2){
		altura = l1;
		comprimento = l2;
	}

}

class main{

	private static quadrado vQuadrado;
	private static retangulo vRetangulo;
	private static circulo vCirculo;

	public static void main(String[] args) {
		vQuadrado = new quadrado(4);
		vRetangulo = new retangulo(4,3);
		vCirculo = new circulo(3);	
		imprimeArea();
	}

	public static double imprimeArea(){
		System.out.print("Area do quadrado: ");
		System.out.println(vQuadrado.getArea());
		System.out.print("Area do retangulo: ");
		System.out.println(vRetangulo.getArea());
		System.out.print("Area do circulo: ");
		System.out.println(vCirculo.getArea());		
		return 0;
	}	

}