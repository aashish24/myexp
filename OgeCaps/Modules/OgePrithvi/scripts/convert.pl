#!/usr/bin/perl

$degrees_per_pixel = 1.0 / ( 256.0 );

$kwl = "mars.kwl";
open ( KWL, ">$kwl" ) or die;
print KWL "archive0.type: local\r\n";

$count = 0;

for ( $lat = -90; $lat <= 60; $lat += 30 )
{
    for ( $long = 0; $long <= 330; $long += 30 )
    {
        $base = sprintf ( "thm_dir_N%02d_%03d", $lat, $long );
        $file = "$base.geom";
        print KWL "archive0.file$count: C:\\aashish\\data\\mars\\$base.png\r\n";
        $count++;
        
        open ( GEOM, ">$file" ) or die;

        print GEOM "type: ossimLlxyProjection\r\n";
        print GEOM "pixel_scale_units: degrees\r\n";
        print GEOM "pixel_scale_xy: ( $degrees_per_pixel, $degrees_per_pixel )\r\n";
        print GEOM "datum: WGE\r\n";
        print GEOM "tie_point_units: degrees\r\n";
        $x = $long - 180;
        $y = $lat + 30;
        print GEOM "tie_point_xy: ($x, $y)\r\n";
        print GEOM "pixel_type: area\r\n";
    }
}
