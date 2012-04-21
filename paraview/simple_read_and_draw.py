import paraview.simple as pv
reader = pv.UnstructuredNetCDFPOPreader(FileName="TEMP.t.t0.1_42l_oilspill12c.00060101.pop.nc/home/aashish/data/climate/TEMP.t.t0.1_42l_oilspill12c.00060101.pop.nc")
pv.Show(reader)
pv.Render()

# Now get the display property and set a lookup table
dp.Lookuptable = pv.MakeBlueToRedLT(0,0.5)
dp.ColorAttributeType='POINT_DATA'
dp.ColorArrayName='TEMP'

# Render again
pv.Render()

