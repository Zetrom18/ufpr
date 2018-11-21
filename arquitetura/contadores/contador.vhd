-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- UFPR, BCC, ci210                        autor: Roberto Hexsel, 02abr2013
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- contador assincrono de 4 bits
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
use work.p_wires.all;

entity contAssincrono4 is
  port(rel, rst : in bit;
       Q : out bit_vector(3 downto 0));
end contAssincrono4;

architecture estrutural of contAssincrono4 is
  component FFT
    generic (prop : time);
    port(rel, rst, set : in bit;
        D : in  bit;
        Q : out bit);
  end component FFT;
  component inv is
    generic (prop : time);
    port(A : in bit; S : out bit);
  end component inv;

  signal val : bit_vector(3 downto 0);
  signal c0,c1,c2 : bit;

begin
  
  U0: FFT generic map (t_FFT) port map (rel,    rst, '1', '1', val(0));
  I0: inv generic map (t_inv) port map (val(0), c0);
  U1: FFT generic map (t_FFT) port map (c0,     rst, '1', '1', val(1));
  I1: inv generic map (t_inv) port map (val(1), c1);
  U2: FFT generic map (t_FFT) port map (c1,     rst, '1', '1', val(2));
  I2: inv generic map (t_inv) port map (val(2), c2);
  U3: FFT generic map (t_FFT) port map (c2,     rst, '1', '1', val(3));
 
  Q <= val;

end estrutural;
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- contador sincrono de 4 bits
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
use work.p_wires.all;

entity contSincrono4 is
  port(rel, rst : in bit;
       Q : out bit_vector(3 downto 0));
end contSincrono4;

architecture estrutural of contSincrono4 is
  component FFT
    generic (prop : time);
    port(rel, rst, set : in bit;
        D : in  bit;
        Q : out bit);
  end component FFT;

  component and2
    generic (prop : time);
    port (a, b : in  bit;
          s    : out bit);
  end component and2;

  signal val : bit_vector(3 downto 0);
  signal a1,a2 : bit;

begin

  U0: FFT generic map (t_FFT)   port map (rel, rst, '1', '1'   , val(0));

  U1: FFT generic map (t_FFT)   port map (rel, rst, '1', val(0), val(1));

  G1: and2 generic map (t_and2) port map (val(0),val(1),a1);
  U2: FFT  generic map (t_FFT)  port map (rel, rst, '1',     a1, val(2));

  G2: and2 generic map (t_and2) port map (a1,val(2),a2 );
  U3: FFT  generic map (t_FFT)  port map (rel, rst, '1',     a2, val(3));
 
  Q <= val;

end estrutural;
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- contador sincrono em anel de 4 bits
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
use work.p_wires.all;

entity contAnel4 is
  port(rel, rst : in bit;
       Q : out bit_vector(3 downto 0));
end contAnel4;

architecture estrutural of contAnel4 is
  component FFD
    generic (prop : time);
    port(rel, rst, set : in bit;
        D : in  bit;
        Q : out bit);
  end component FFD;

  signal val : bit_vector(3 downto 0);

begin

  -- projeto incompleto; acrescente o que for necessario
--  U0: FFD generic map (t_FFD) port map (rel, , , , );
--  U1: FFD generic map (t_FFD) port map (rel, , , , );
--  U2: FFD generic map (t_FFD) port map (rel, , , , );
--  U3: FFD generic map (t_FFD) port map (rel, , , , );

  Q <= val;

end estrutural;
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- registrador de deslocamento de 4 bits com carga paralela sincrona
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
use work.p_wires.all;

entity regDesloc4 is
  port(rel, rst, car : in bit;
        D : in  bit_vector(3 downto 0);
        Q : out bit_vector(3 downto 0));
end regDesloc4;

architecture estrutural of regDesloc4 is
  component FFD
    generic (prop : time);
    port(rel, rst, set : in bit;
        D : in  bit;
        Q : out bit);
  end component FFD;

  component mux2
    port (a, b, s : in  bit;    -- sel=0: z <= a
          z       : out bit);
  end component mux2;

  signal est, inp : bit_vector(3 downto 0);

begin

  -- sinal carga ativo em '1'

--  M0: mux2 port map ( , , car, );
--  U0: FFD generic map (t_FFD) port map (rel, rst, '1', , );

--  M1: mux2 port map ( , ,car, );
--  U1: FFD generic map (t_FFD) port map (rel, rst, '1', , );

--  M2: mux2 port map ( , ,car, );
--  U2: FFD generic map (t_FFD) port map (rel, rst, '1', , );

--  M3: mux2 port map ( , ,car, );
--  U3: FFD generic map (t_FFD) port map (rel, rst, '1', , );
    
  Q <= est;

end estrutural;
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
