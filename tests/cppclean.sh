excluded="static data"
command="cppclean $dir/src | egrep -Ev '$excluded'"
echo $command
then
  echo "Problem with cppclean command"
  eval $command