git filter-branch --env-filter '

ANTIGUO_EMAIL="jghernande@bch.bancodechile.cl"
NUEVO_EMAIL="juanguillermoalarcon@gmail.com"
NUEVO_USUARIO="berracode"

if [ "$GIT_COMMITTER_EMAIL"="$ANTIGUO_EMAIL" ]
then
    export GIT_COMMITTER_EMAIL="$NUEVO_EMAIL"
    export GIT_COMMITTER_NAME="$NUEVO_USUARIO"
fi
if [ "$GIT_AUTHOR_EMAIL"="$ANTIGUO_EMAIL" ]
then
    export GIT_AUTHOR_EMAIL="$NUEVO_EMAIL"
    export GIT_AUTHOR_NAME="$NUEVO_USUARIO"
fi
' --tag-name-filter cat -- --branches --tags
