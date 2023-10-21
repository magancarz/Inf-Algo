with Ada.Text_IO;
with Ada.Containers.Vectors;

procedure Traveler is
   Max_Moves : constant Integer := 10;
   M        : constant Integer := 5;
   N        : constant Integer := 5;
   K        : constant Integer := 5;

   type Traveler_Type is record
      Id  : Integer;
      X, Y : Integer;
   end record;

   type Move_Track_Type is record
      From_Below : Integer;
      From_Side  : Integer;
   end record;

   package Travelers_Vectors is new Ada.Containers.Vectors
     (Index_Type   => Integer,
      Element_Type => Traveler_Type);

   package Move_Grid_Vectors is new Ada.Containers.Vectors
     (Index_Type   => Integer,
      Element_Type => Move_Track_Type);

   Travelers : Travelers_Vectors.Vector;
   Move_Grid : Move_Grid_Vectors.Vector;

   Next_Free_Id : Integer := 0;

   protected Mutex is
      entry Lock;
      entry Unlock;
   private
      Lock_Flag, Unlock_Flag : Boolean := False;
   end Mutex;

   procedure Lock is
   begin
      if not Lock_Flag then
         Lock_Flag := True;
      else
         accept Unlock;
         Lock_Flag := True;
      end if;
   end Lock;

   procedure Unlock is
   begin
      if Unlock_Flag then
         Lock_Flag := False;
      else
         accept Lock;
         Lock_Flag := False;
      end if;
   end Unlock;

   procedure Move (T : in out Traveler_Type;
                   Grid : in out Integer_Arr;
                   Move_Grid : in out Move_Track_Type_Arr) is
      Directions : constant array (0 .. 3) of Integer_Arr
        := ((-1, 0), (1, 0), (0, -1), (0, 1));
      Move       : Integer_Arr;
      New_X, New_Y : Integer;
      Num_Of_Iterations : Integer := 0;
   begin
      loop
         Move := Directions (Natural (Integer (Ada.Text_IO.Random_IO.Random) mod 4));
         New_X := T.X + Move (1);
         New_Y := T.Y + Move (2);

         if New_X >= 0 and then New_X < M and then
            New_Y >= 0 and then New_Y < N and then Grid (New_X, New_Y) /= 1 then
            exit;
         end if;

         Num_Of_Iterations := Num_Of_Iterations + 1;
         exit when Num_Of_Iterations >= 10;
      end loop;

      if New_X >= 0 and then New_X < M and then New_Y >= 0 and then New_Y < N then
         if Move (1) /= 0 then
            declare
               Min : Integer;
            begin
               if T.X < New_X then
                  Min := T.X;
               else
                  Min := New_X;
               end if;

               Move_Grid (Min)(T.Y).From_Below := 1;
            end;
         else
            declare
               Min : Integer;
            begin
               if T.Y < New_Y then
                  Min := T.Y;
               else
                  Min := New_Y;
               end if;

               Move_Grid (T.X)(Min).From_Side := 1;
            end;
         end if;

         Grid (T.X, T.Y) := -1;
         T.X := New_X;
         T.Y := New_Y;
         Grid (T.X, T.Y) := T.Id;
      end if;
   end Move;

   procedure Traveler_Movement (T : in out Traveler_Type;
                                Grid : in out Integer_Arr;
                                Move_Grid : in out Move_Track_Type_Arr;
                                Moves : Integer) is
   begin
      for Move in 1 .. Moves loop
         Move (T, Grid, Move_Grid);
         Delay_Milliseconds (Ada.Text_IO.Duration
           (Ada.Text_IO.Random_IO.Random (Ada.Text_IO.Duration (0, 0), Ada.Text_IO.Duration (0, 1000))));
      end loop;
   end Traveler_Movement;

   procedure Spawn_Traveler (Grid : in out Integer_Arr;
                             Next_Free_Id : in out Integer;
                             T : in out Traveler_Type) is
      X, Y : Integer;
   begin
      loop
         X := Natural (Integer (Ada.Text_IO.Random_IO.Random) mod M);
         Y := Natural (Integer (Ada.Text_IO.Random_IO.Random) mod N);

         if Grid (X, Y) = -1 then
            exit;
         end if;
      end loop;

      Grid (X, Y) := Next_Free_Id;
      T.Id := Next_Free_Id;
      T.X := X;
      T.Y := Y;
      Next_Free_Id := Next_Free_Id + 1;
   end Spawn_Traveler;

   procedure Spawn_Travelers is
   begin
      for I in 1 .. K loop
         if Next_Free_Id < (M * N - 1) and then Natural (Integer (Ada.Text_IO.Random_IO.Random) mod 100) < 30 then
            Spawn_Traveler (Grid, Next_Free_Id, Travelers (Next_Free_Id));
         end if;

         Delay_Milliseconds (Ada.Text_IO.Duration (0, 100000));
      end loop;
   end Spawn_Travelers;

   procedure Snap (Move : Integer;
                  Grid : in out Integer_Arr;
                  Move_Grid : in out Move_Track_Type_Arr;
                  Moves : Integer) is
   begin
      Ada.Text_IO.Put_Line ("Move: " & Integer'Image (Move));

      for I in 1 .. M loop
         for J in 1 .. N loop
            Ada.Text_IO.Put (1, 1);
            if Grid (I, J) = -1 then
               Ada.Text_IO.Put ("  ");
            else
               Ada.Text_IO.Put (2, Integer'Image (Grid (I, J)));
            end if;
            if Move_Grid (I)(J).From_Side = 1 then
               Ada.Text_IO.Set_Foreground (Ada.Text_IO.Red);
            else
               Ada.Text_IO.Reset_Foreground;
            end if;
            Ada.Text_IO.Put ("|");
         end loop;
         Ada.Text_IO.New_Line;
         for K in 1 .. N loop
            if Move_Grid (I)(K).From_Below = 1 then
               Ada.Text_IO.Set_Foreground (Ada.Text_IO.Red);
            else
               Ada.Text_IO.Reset_Foreground;
            end if;
            Ada.Text_IO.Put ("---");
         end loop;
         Ada.Text_IO.New_Line;
      end loop;
   end Snap;

   procedure Snapshot (Moves : Integer) is
   begin
      for Move in 1 .. Moves loop
         Snap (Move, Grid, Move_Grid, Max_Moves);
         Delay_Milliseconds (Ada.Text_IO.Duration (0, 100000000));
      end loop;
   end Snapshot;

   procedure Main is
   begin
      Ada.Text_IO.Put_Line ("Traveler Simulation");

      Ada.Text_IO.Random_IO.Reset;

      declare
         type Integer_Arr is array (1 .. M, 1 .. N) of Integer;
         type Move_Track_Type_Arr is array (1 .. M, 1 .. N) of Move_Track_Type;
         Grid : Integer_Arr := (others => (others => -1));
         Move_Grid : Move_Track_Type_Arr := (others => (others => (From_Below => -1, From_Side => -1)));
         Next_Free_Id : Integer := 0;
         Travelers : Travelers_Vectors.Vector := Travelers_Vectors.Null_Vector;
      begin
         for I in 1 .. K loop
            declare
               T : Traveler_Type;
            begin
               Spawn_Traveler (Grid, Next_Free_Id, T);
               Travelers.Append (T);
            end;
         end loop;

         for I in 1 .. K loop
            declare
               T : Traveler_Type := Travelers (I);
            begin
               Traveler_Movement (T, Grid, Move_Grid, Max_Moves);
            end;
         end loop;

         Spawn_Travelers;
         Snapshot (Max_Moves);
      end;
   end Main;
begin
   Main;
end Traveler;
