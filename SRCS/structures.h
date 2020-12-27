typedef struct			s_info
{
	char				*type;
	int					n_flag;
	char				**args;
	int					args_num;
	void				*next;
	int					in;
	int					out;
	int					dup_in;
	int					dup_out;
	char				**redirs;
	int					cur_i;
	int					pipe;
	int					pipe_prev;
	int					right_redir;
	int					left_redir;
	int					arg_i;
	int					res_prev;
	char				**envp;
}						t_info;

typedef struct		s_general
{
	int				*pipe_fd;
	int				pipe_in_prev_command;
	int				other_command;
	int				dup_in;
	int				dup_out;
	}				t_general;		

typedef struct		s_red_utils
{
	int				redir_num;
	int 			cur_i;
}					t_red_utils;

typedef struct		s_env
{
	char			*type;
	char			*value;
	int				class;
	struct s_env	*next;	
}					t_env;

typedef struct		s_line_check
{
	int				symb;
	int				space;
}					t_line_check;